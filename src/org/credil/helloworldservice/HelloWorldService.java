package org.credil.helloworldservice;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.os.ServiceManager;    //Android internal API
import android.util.Log;

/**
 *   HelloWorldService is a normal Android service declared in a normal
 *   AndroidManifest.xml. It therefore will be instantiated when the correct
 *   Intent is launched. Upon that happening in the onBind methods we use
 *   ServiceManager.getService.
 */
public class HelloWorldService extends Service {
    private final static String LOG_TAG = HelloWorldService.class.getSimpleName();
    private IBinder mIBinder;


    /**
     *  Initialize the native library given a binder object.
     **/
    private native Binder nativeInit();

    public IBinder onBind(Intent intent) {

        System.loadLibrary("helloworldservice");
        mIBinder = nativeInit();
        if (mIBinder == null) {
            Log.e(LOG_TAG, "Hello service not found is/system/bin/helloworldservice running?");
            return null;
        }
        return mIBinder;
    }
}
