package com.spencerfricke.tango_visual_aid;

import android.app.Activity;
import android.content.ComponentName;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.Bundle;
import android.os.Vibrator;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends Activity {

    Vibrator vibrator;
    private CustomDrawerLayout mDrawerLayout;
    private Button mChangeIpButton;
    private EditText newIpText;

    // Tango Service connection.
    ServiceConnection mTangoServiceConnection = new ServiceConnection() {
        public void onServiceConnected(ComponentName name, IBinder service) {
            // Synchronization around MainActivity object is to avoid
            // Tango disconnect in the middle of the connecting operation.
            TangoJniNative.onTangoServiceConnected(service);
        }

        public void onServiceDisconnected(ComponentName name) {
            // Handle this if you need to gracefully shutdown/retry
            // in the event that Tango itself crashes/gets upgraded while running.
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TangoJniNative.onCreate(this);

        // Need to activate the Vibrator service before it can be used
        vibrator = (Vibrator)getSystemService(VIBRATOR_SERVICE);
        mChangeIpButton = (Button)findViewById(R.id.change_ip_button);
        newIpText = (EditText)findViewById(R.id.ip_address_input);
        mDrawerLayout = (CustomDrawerLayout) findViewById(R.id.drawer_layout);


        mChangeIpButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View arg0) {
                String newIp = newIpText.getText().toString();
                TangoJniNative.newIp(newIp);
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        TangoInitializationHelper.bindTangoService(this, mTangoServiceConnection);
    }

    @Override
    protected void onPause() {
        super.onPause();
        // Disconnect from Tango Service, release all the resources that the app is
        // holding from Tango Service.
        TangoJniNative.onPause();
        unbindService(mTangoServiceConnection);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        TangoJniNative.onDestroy();
    }

    // Creates viberation pulse
    // interval is the length of the viberation and dot is time between
    // A higher dot results in a slower pulse
    public void pulse(int dot) {
        int interval = 100;
        long[] pattern = {
                dot, interval, dot, interval,
                dot, interval, dot, interval,
                dot, interval, dot, interval,
                dot, interval, dot, interval,
                dot, interval, dot, interval,
                dot, interval, dot, interval,
                dot, interval, dot, interval,
                dot, interval, dot, interval
        };
        vibrator.vibrate(pattern, -1);

        // Also be aware if this callback updates the UI it can crash due to
        // having too many threads calling at once so use Activity.runOnUiThread
    }
}
