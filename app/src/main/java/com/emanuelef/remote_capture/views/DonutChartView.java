/*
 * This file is part of Aspida.
 *
 * Aspida is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Aspida is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Aspida.  If not, see <http://www.gnu.org/licenses/>.
 */

package com.emanuelef.remote_capture.views;

import android.animation.ValueAnimator;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.RectF;
import android.graphics.Typeface;
import android.util.AttributeSet;
import android.view.View;
import android.view.animation.DecelerateInterpolator;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

/**
 * Donut (ring) chart showing the proportion of two values (e.g. bytes sent vs received).
 * No external library required — drawn entirely on Canvas.
 */
public class DonutChartView extends View {

    private final Paint mArcPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint mTrackPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint mCenterLabelPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint mCenterValuePaint = new Paint(Paint.ANTI_ALIAS_FLAG);

    private final RectF mOval = new RectF();

    private int mColor1 = 0xFF1565C0;   // blue  – slice 1
    private int mColor2 = 0xFF00ACC1;   // teal  – slice 2

    private float mValue1 = 0f;
    private float mValue2 = 0f;

    private String mLabel1 = "Sent";
    private String mLabel2 = "Received";
    private String mCenterLabel = "Total";
    private String mCenterValue = "0 B";

    // animated sweep angle for slice 1 (0–360)
    private float mAnimatedSweep1 = 0f;

    private static final float STROKE_RATIO = 0.18f; // ring thickness relative to radius
    private static final float GAP_DEG = 3f;          // gap between slices

    public DonutChartView(Context context) {
        super(context);
        init();
    }

    public DonutChartView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public DonutChartView(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }

    private void init() {
        mTrackPaint.setStyle(Paint.Style.STROKE);
        mTrackPaint.setColor(0x1A000000);
        mTrackPaint.setStrokeCap(Paint.Cap.ROUND);

        mArcPaint.setStyle(Paint.Style.STROKE);
        mArcPaint.setStrokeCap(Paint.Cap.BUTT);

        mCenterLabelPaint.setTextAlign(Paint.Align.CENTER);
        mCenterLabelPaint.setColor(0xFF90A4AE);
        mCenterLabelPaint.setTypeface(Typeface.DEFAULT);

        mCenterValuePaint.setTextAlign(Paint.Align.CENTER);
        mCenterValuePaint.setColor(0xFF1565C0);
        mCenterValuePaint.setTypeface(Typeface.DEFAULT_BOLD);
    }

    /**
     * Update chart data. Triggers a smooth animation.
     *
     * @param value1     raw value for slice 1 (sent)
     * @param value2     raw value for slice 2 (received)
     * @param centerValue formatted string shown in the center (e.g. "12.5 MB")
     */
    public void setData(float value1, float value2, String centerValue) {
        mValue1 = value1;
        mValue2 = value2;
        mCenterValue = (centerValue != null) ? centerValue : "0 B";

        float total = mValue1 + mValue2;
        float targetSweep = (total > 0) ? (mValue1 / total) * (360f - 2 * GAP_DEG) : 0f;

        ValueAnimator animator = ValueAnimator.ofFloat(mAnimatedSweep1, targetSweep);
        animator.setDuration(600);
        animator.setInterpolator(new DecelerateInterpolator());
        animator.addUpdateListener(a -> {
            mAnimatedSweep1 = (float) a.getAnimatedValue();
            invalidate();
        });
        animator.start();
    }

    public void setColors(int color1, int color2) {
        mColor1 = color1;
        mColor2 = color2;
        invalidate();
    }

    public void setLabels(String label1, String label2, String centerLabel) {
        mLabel1 = label1;
        mLabel2 = label2;
        mCenterLabel = centerLabel;
        invalidate();
    }

    @Override
    protected void onDraw(@NonNull Canvas canvas) {
        super.onDraw(canvas);

        int w = getWidth();
        int h = getHeight();
        float size = Math.min(w, h);
        float cx = w / 2f;
        float cy = h / 2f;
        float radius = size / 2f * 0.75f;
        float stroke = radius * STROKE_RATIO;

        mTrackPaint.setStrokeWidth(stroke);
        mArcPaint.setStrokeWidth(stroke);

        // Background track
        canvas.drawCircle(cx, cy, radius, mTrackPaint);

        mOval.set(cx - radius, cy - radius, cx + radius, cy + radius);

        float total = mValue1 + mValue2;

        if (total <= 0) {
            // draw empty state ring
            mArcPaint.setColor(0xFFECEFF1);
            canvas.drawArc(mOval, -90f, 360f, false, mArcPaint);
        } else {
            float sweep1 = mAnimatedSweep1;
            float sweep2 = (360f - 2 * GAP_DEG) - sweep1;

            // Slice 1 (sent) — blue
            mArcPaint.setColor(mColor1);
            canvas.drawArc(mOval, -90f + GAP_DEG / 2f, sweep1, false, mArcPaint);

            // Slice 2 (received) — teal
            mArcPaint.setColor(mColor2);
            canvas.drawArc(mOval, -90f + GAP_DEG / 2f + sweep1 + GAP_DEG, sweep2, false, mArcPaint);
        }

        // Center label (small) and value (bold, bigger)
        float labelSize = size * 0.065f;
        float valueSize = size * 0.10f;

        mCenterLabelPaint.setTextSize(labelSize);
        mCenterValuePaint.setTextSize(valueSize);

        float textOffset = (mCenterValuePaint.descent() - mCenterValuePaint.ascent()) / 2f
                - mCenterValuePaint.descent();

        canvas.drawText(mCenterValue, cx, cy + textOffset, mCenterValuePaint);
        canvas.drawText(mCenterLabel, cx, cy + textOffset + labelSize * 1.3f, mCenterLabelPaint);
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        int size = MeasureSpec.getSize(widthMeasureSpec);
        // Square view
        setMeasuredDimension(size, size);
    }
}
