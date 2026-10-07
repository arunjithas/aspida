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

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.LinearGradient;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.Shader;
import android.graphics.Typeface;
import android.util.AttributeSet;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import java.util.ArrayList;
import java.util.List;

/**
 * Two-line graph (sent/received throughput over time).
 * Drawn entirely on Canvas — no external library required.
 */
public class LineGraphView extends View {

    public static final int MAX_POINTS = 60;

    private final List<Float> mSentSeries = new ArrayList<>();
    private final List<Float> mRcvdSeries = new ArrayList<>();

    private int mColorSent = 0xFF1565C0;
    private int mColorRcvd = 0xFF00ACC1;

    private final Paint mGridPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint mLinePaintSent = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint mLinePaintRcvd = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint mFillPaintSent = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint mFillPaintRcvd = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint mAxisPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint mLabelPaint = new Paint(Paint.ANTI_ALIAS_FLAG);

    private final Path mPathSent = new Path();
    private final Path mPathRcvd = new Path();
    private final Path mFillSent = new Path();
    private final Path mFillRcvd = new Path();

    // Y-axis label formatter (set from outside)
    private YAxisFormatter mFormatter = value -> String.format("%.0f B", value);

    public interface YAxisFormatter {
        String format(float value);
    }

    public LineGraphView(Context context) {
        super(context);
        init();
    }

    public LineGraphView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public LineGraphView(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }

    private void init() {
        mGridPaint.setColor(0x18000000);
        mGridPaint.setStrokeWidth(1f);
        mGridPaint.setStyle(Paint.Style.STROKE);

        mLinePaintSent.setStyle(Paint.Style.STROKE);
        mLinePaintSent.setStrokeWidth(3f);
        mLinePaintSent.setStrokeCap(Paint.Cap.ROUND);
        mLinePaintSent.setStrokeJoin(Paint.Join.ROUND);

        mLinePaintRcvd.setStyle(Paint.Style.STROKE);
        mLinePaintRcvd.setStrokeWidth(3f);
        mLinePaintRcvd.setStrokeCap(Paint.Cap.ROUND);
        mLinePaintRcvd.setStrokeJoin(Paint.Join.ROUND);

        mFillPaintSent.setStyle(Paint.Style.FILL);
        mFillPaintRcvd.setStyle(Paint.Style.FILL);

        mAxisPaint.setColor(0x22000000);
        mAxisPaint.setStrokeWidth(1.5f);

        mLabelPaint.setColor(0xFFB0BEC5);
        mLabelPaint.setTextSize(28f);
        mLabelPaint.setTypeface(Typeface.DEFAULT);
        mLabelPaint.setTextAlign(Paint.Align.RIGHT);
    }

    public void setColors(int colorSent, int colorRcvd) {
        mColorSent = colorSent;
        mColorRcvd = colorRcvd;
        invalidate();
    }

    public void setYAxisFormatter(YAxisFormatter formatter) {
        mFormatter = formatter;
    }

    /**
     * Add a new data point. Values should be per-interval deltas (bytes/sec or similar).
     */
    public void addPoint(float sentDelta, float rcvdDelta) {
        mSentSeries.add(Math.max(0f, sentDelta));
        mRcvdSeries.add(Math.max(0f, rcvdDelta));

        while (mSentSeries.size() > MAX_POINTS) mSentSeries.remove(0);
        while (mRcvdSeries.size() > MAX_POINTS) mRcvdSeries.remove(0);

        invalidate();
    }

    public void clearData() {
        mSentSeries.clear();
        mRcvdSeries.clear();
        invalidate();
    }

    @Override
    protected void onDraw(@NonNull Canvas canvas) {
        super.onDraw(canvas);

        float densityMultiplier = getContext().getResources().getDisplayMetrics().density;
        float labelTextSize = 9f * densityMultiplier;
        mLabelPaint.setTextSize(labelTextSize);

        float leftPad = labelTextSize * 4.5f;
        float rightPad = 16f;
        float topPad = 16f;
        float bottomPad = labelTextSize * 2f;

        float graphLeft = leftPad;
        float graphRight = getWidth() - rightPad;
        float graphTop = topPad;
        float graphBottom = getHeight() - bottomPad;
        float graphW = graphRight - graphLeft;
        float graphH = graphBottom - graphTop;

        if (graphW <= 0 || graphH <= 0) return;

        // Determine max value across both series
        float maxVal = 1f;
        for (float v : mSentSeries) maxVal = Math.max(maxVal, v);
        for (float v : mRcvdSeries) maxVal = Math.max(maxVal, v);
        // Round up to a nice value
        maxVal = niceMax(maxVal);

        // Draw horizontal grid lines (4 lines)
        int gridLines = 4;
        for (int i = 0; i <= gridLines; i++) {
            float y = graphBottom - (i / (float) gridLines) * graphH;
            canvas.drawLine(graphLeft, y, graphRight, y, mGridPaint);

            // Y-axis label
            float labelVal = (i / (float) gridLines) * maxVal;
            String label = mFormatter.format(labelVal);
            canvas.drawText(label, graphLeft - 6f, y + labelTextSize / 3f, mLabelPaint);
        }

        // Bottom axis
        canvas.drawLine(graphLeft, graphBottom, graphRight, graphBottom, mAxisPaint);

        int n = mSentSeries.size();
        if (n < 2) return;

        float xStep = graphW / (float) (MAX_POINTS - 1);
        float startX = graphRight - (n - 1) * xStep;

        // Build paths
        mPathSent.reset();
        mPathRcvd.reset();
        mFillSent.reset();
        mFillRcvd.reset();

        float firstXSent = startX;
        float firstXRcvd = startX;

        for (int i = 0; i < n; i++) {
            float x = startX + i * xStep;
            float ySent = graphBottom - (mSentSeries.get(i) / maxVal) * graphH;
            float yRcvd = graphBottom - (mRcvdSeries.get(i) / maxVal) * graphH;

            if (i == 0) {
                mPathSent.moveTo(x, ySent);
                mPathRcvd.moveTo(x, yRcvd);
                mFillSent.moveTo(x, graphBottom);
                mFillSent.lineTo(x, ySent);
                mFillRcvd.moveTo(x, graphBottom);
                mFillRcvd.lineTo(x, yRcvd);
                firstXSent = x;
                firstXRcvd = x;
            } else {
                mPathSent.lineTo(x, ySent);
                mPathRcvd.lineTo(x, yRcvd);
                mFillSent.lineTo(x, ySent);
                mFillRcvd.lineTo(x, yRcvd);
            }
        }

        // Close fill paths
        float lastX = startX + (n - 1) * xStep;
        mFillSent.lineTo(lastX, graphBottom);
        mFillSent.lineTo(firstXSent, graphBottom);
        mFillSent.close();

        mFillRcvd.lineTo(lastX, graphBottom);
        mFillRcvd.lineTo(firstXRcvd, graphBottom);
        mFillRcvd.close();

        // Apply gradient shaders for fill areas
        mFillPaintSent.setShader(new LinearGradient(
                0, graphTop, 0, graphBottom,
                adjustAlpha(mColorSent, 0.25f), adjustAlpha(mColorSent, 0.0f),
                Shader.TileMode.CLAMP));

        mFillPaintRcvd.setShader(new LinearGradient(
                0, graphTop, 0, graphBottom,
                adjustAlpha(mColorRcvd, 0.20f), adjustAlpha(mColorRcvd, 0.0f),
                Shader.TileMode.CLAMP));

        canvas.drawPath(mFillRcvd, mFillPaintRcvd);
        canvas.drawPath(mFillSent, mFillPaintSent);

        // Draw lines on top
        mLinePaintSent.setColor(mColorSent);
        mLinePaintRcvd.setColor(mColorRcvd);

        canvas.drawPath(mPathRcvd, mLinePaintRcvd);
        canvas.drawPath(mPathSent, mLinePaintSent);
    }

    /** Returns a "nice" ceiling for the given max value (1, 2, 5, 10, 20, 50, …). */
    private float niceMax(float max) {
        if (max <= 0) return 1f;
        double mag = Math.pow(10, Math.floor(Math.log10(max)));
        double norm = max / mag;
        double nice;
        if (norm <= 1) nice = 1;
        else if (norm <= 2) nice = 2;
        else if (norm <= 5) nice = 5;
        else nice = 10;
        return (float) (nice * mag);
    }

    private int adjustAlpha(int color, float alpha) {
        int a = Math.round(alpha * 255);
        return (color & 0x00FFFFFF) | (a << 24);
    }
}
