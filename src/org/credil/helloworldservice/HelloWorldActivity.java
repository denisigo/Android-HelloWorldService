package org.credil.helloworldservice;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.widget.TextView;
//import android.os.ServiceManager;    //Android internal API
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/**
 * Sample client using purely public Android interfaces
 */
public class HelloWorldActivity extends Activity {
    private static final String LOG_TAG = HelloWorldActivity.class.getSimpleName();

    TextView mHelloBox;
    IHelloWorld mIHelloWorld;

    public ServiceConnection serviceConnection = new ServiceConnection() {
        public void onServiceConnected(ComponentName name, IBinder service) {
            /*
            Log.d(LOG_TAG, "Service connected");
            mIHelloWorld = IHelloWorld.Stub.asInterface(service);
            mHelloBox.append("connected\n");


            try {
                mIHelloWorld.setListener(new HelloWorldListener());
            } catch (RemoteException e) {
                Log.w(LOG_TAG," Failed to invoke setListener:" + e.getMessage(),e);
            }

            try {
                mIHelloWorld.hellothere("Calling from Java");
                mIHelloWorld.hellohere("Calling from Java222222");
            } catch (RemoteException e) {
                Log.w(LOG_TAG," Failed to invoke hellothere:" + e.getMessage(),e);
            }
            */
        }

        public void onServiceDisconnected(ComponentName name) {
            mHelloBox.append("diconnected\n");
            Log.e(LOG_TAG, "disconnected");
            //This is where the current story ends. once disconnected we are not able to automatically reconnect
            mIHelloWorld = null;
        }
    };

    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.hello);

        mHelloBox = (TextView) findViewById(R.id.HelloView01);
        mHelloBox.setText("start\n");


        //IBinder binder = ServiceManager.getService("org.credil.helloworldservice.IHelloWorld");

        Method method = null;
        try {
            method = Class.forName("android.os.ServiceManager").getMethod("getService", String.class);
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
        IBinder binder = null;
        try {
            binder = (IBinder) method.invoke(null, "org.credil.helloworldservice.IHelloWorld");
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        }

        mIHelloWorld = IHelloWorld.Stub.asInterface(binder);
        mHelloBox.append("connected2222244444\n");


        try {
            mIHelloWorld.setListener(new HelloWorldListener());
        } catch (RemoteException e) {
            Log.w(LOG_TAG," Failed to invoke setListener:" + e.getMessage(),e);
        }

        try {
            mIHelloWorld.hellothere("Calling from Java33333");
            mIHelloWorld.hellohere("Calling from Java22222244444444");
        } catch (RemoteException e) {
            Log.w(LOG_TAG," Failed to invoke hellothere:" + e.getMessage(),e);
        }


        //We can currently not perform a bindService because the native code
        //did not register to the activity manager
        //bindService(new Intent("org.credil.helloworldservice.IHelloWorld"),serviceConnection, BIND_AUTO_CREATE);
    }

    public void onDestroy(){
        super.onDestroy();
        unbindService(serviceConnection);
    }


    private class HelloWorldListener extends IHelloWorldListener.Stub {

        private static final String TAG = "HelloWorldListener";

        @Override
        public IBinder asBinder() {
            return this;
        }

        @Override
        public void onStatusChanged(int status) throws RemoteException {
            mHelloBox.append(status+"\n");
        }
    }
}