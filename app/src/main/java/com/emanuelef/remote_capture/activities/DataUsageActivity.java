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

package com.emanuelef.remote_capture.activities;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.emanuelef.remote_capture.CaptureService;
import com.emanuelef.remote_capture.R;
import com.emanuelef.remote_capture.Utils;
import com.emanuelef.remote_capture.model.CaptureStats;
import com.emanuelef.remote_capture.views.DonutChartView;
import com.emanuelef.remote_capture.views.LineGraphView;

/**
 * Graphical data-usage dashboard.
 *
 * Shows:
 *  – Summary cards: bytes sent/received, packets sent/received
 *  – Donut chart: proportion of sent vs received bytes
 *  – Line graph: per-update throughput trend (last 60 samples)
 *  – Connections card: active, total, DNS queries
 */
public class DataUsageActivity extends BaseActivity {

    // Summary card text views
    private TextView mBytesSent;
    private TextView mBytesRcvd;
    private TextView mPktsSent;
    private TextView mPktsRcvd;

    // Donut chart + legend
    private DonutChartView mDonutChart;
    private TextView mLegendSentVal;
    private TextView mLegendRcvdVal;

    // Line graph
    private LineGraphView mLineGraph;
    private View mGraphNoData;

    // Connections card
    private TextView mActiveConns;
    private TextView mTotConns;
    private TextView mDnsQueries;

    // Previous stats to compute deltas for the line graph
    private long mPrevBytesSent = -1;
    private long mPrevBytesRcvd = -1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setTitle(R.string.data_usage);
        displayBackAction();
        setContentView(R.layout.activity_data_usage);

        // Summary cards
        mBytesSent   = findViewById(R.id.stat_bytes_sent);
        mBytesRcvd   = findViewById(R.id.stat_bytes_rcvd);
        mPktsSent    = findViewById(R.id.stat_pkts_sent);
        mPktsRcvd    = findViewById(R.id.stat_pkts_rcvd);

        // Donut
        mDonutChart    = findViewById(R.id.donut_chart);
        mLegendSentVal = findViewById(R.id.legend_sent_val);
        mLegendRcvdVal = findViewById(R.id.legend_rcvd_val);

        mDonutChart.setLabels(
                getString(R.string.bytes_sent),
                getString(R.string.bytes_rcvd),
                getString(R.string.total));

        // Graph
        mLineGraph   = findViewById(R.id.line_graph);
        mGraphNoData = findViewById(R.id.graph_no_data);

        // Format Y-axis labels as human-readable byte sizes
        mLineGraph.setYAxisFormatter(value -> Utils.formatBytes((long) value));

        // Connections card
        mActiveConns = findViewById(R.id.stat_active_conns);
        mTotConns    = findViewById(R.id.stat_tot_conns);
        mDnsQueries  = findViewById(R.id.stat_dns_queries);

        // Observe live stats from the capture service
        CaptureService.observeStats(this, this::updateStats);
        CaptureService.askStatsDump();
    }

    private void updateStats(CaptureStats stats) {
        // ── Summary cards ──
        mBytesSent.setText(Utils.formatBytes(stats.bytes_sent));
        mBytesRcvd.setText(Utils.formatBytes(stats.bytes_rcvd));
        mPktsSent.setText(Utils.formatIntShort(stats.pkts_sent));
        mPktsRcvd.setText(Utils.formatIntShort(stats.pkts_rcvd));

        // ── Donut chart ──
        long totalBytes = stats.bytes_sent + stats.bytes_rcvd;
        String totalStr = Utils.formatBytes(totalBytes);

        mDonutChart.setData(stats.bytes_sent, stats.bytes_rcvd, totalStr);
        mLegendSentVal.setText(Utils.formatBytes(stats.bytes_sent));
        mLegendRcvdVal.setText(Utils.formatBytes(stats.bytes_rcvd));

        // ── Line graph (throughput deltas) ──
        if (mPrevBytesSent >= 0) {
            float deltaSent = Math.max(0f, stats.bytes_sent - mPrevBytesSent);
            float deltaRcvd = Math.max(0f, stats.bytes_rcvd - mPrevBytesRcvd);
            mLineGraph.addPoint(deltaSent, deltaRcvd);

            if (mGraphNoData.getVisibility() == View.VISIBLE)
                mGraphNoData.setVisibility(View.GONE);
        }
        mPrevBytesSent = stats.bytes_sent;
        mPrevBytesRcvd = stats.bytes_rcvd;

        // ── Connections card ──
        mActiveConns.setText(Utils.formatNumber(this, stats.active_conns));
        mTotConns.setText(Utils.formatNumber(this, stats.tot_conns));
        mDnsQueries.setText(Utils.formatNumber(this, stats.num_dns_queries));
    }
}
