/*
 * HelloWorld Service driver.
 * Copyright (C) 2009 Michael Richardson <mcr@credil.org>
 *
 * Released under the terms of the file ../NOTICE
 */
#define LOG_TAG "HelloWorld/Service"

#include <sys/types.h>
#include <unistd.h>
#include <grp.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/IBinder.h>
#include <utils/String16.h>
#include <utils/String8.h>
#include "helloworldservice.h"

#include <utils/Log.h>
#include <jni.h>
#include "helloworldservice.h"


int main(int argc, char *argv[])
{
	/**
	 * The addService method takes a service name and a IBinder object
	 *  This static methods initializes a new HelloWorldService
	 *  and "registers" it to the default service manager.
	 *  This can not be called in context where the service
	 *  is not running as system service
	 **/
//	defaultServiceManager()->addService(
	//				    IHelloWorld::descriptor, new HelloWorldService());

	android::ProcessState::self()->startThreadPool();
	LOGI("Hello Service is now ready");

	android::IPCThreadState::self()->joinThreadPool();
	return(0);
}



jobject nativeInit(JNIEnv *, jobject);


/**
 * Holder for the WM we hope to run in;
 */
static JavaVM *javaVM;

jint JNI_OnLoad(JavaVM* vm, void* reserved){
	JNIEnv *env = NULL;

	jclass clazz;

	/* Keep a reference to the vm. the vm is valid during the full scope
	 * of the library
	 */
	javaVM = vm;
	LOGI("%s",__FUNCTION__);


	if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
		return JNI_ERR;
	}

	clazz = env->FindClass("org/credil/helloworldservice/HelloWorldService");
	if (!clazz){
		LOGI("Failed to load the HelloWorldService class");
	}

	JNINativeMethod sMethods[] = {
    /*
     * funcPtr generated using javah on the service class
     * Class:     org_credil_helloworldservice_HelloWorldService
     * Method:    nativeInit
     * Signature: ()Landroid/os/Binder;
     */
		{"nativeInit","()Landroid/os/Binder;", (void*)nativeInit}
	};


	if (env->RegisterNatives(clazz,sMethods,sizeof(sMethods)/ sizeof(JNINativeMethod)) != JNI_OK){
		LOGI("%s Failed to register native method",__FUNCTION__);
	}
    
	return JNI_VERSION_1_4;
}

jobject nativeInit(JNIEnv * env , jobject object){
	LOGI("%s What do do with this binder",__FUNCTION__);
	jclass cls = env->FindClass("android/os/Binder");
	if(!cls) {
		LOGE("%s: failed to get Binder class reference", __FUNCTION__);
		return NULL;
	}

	jmethodID constr = env->GetMethodID(cls, "<init>", "()V");
	if(!constr) {
		LOGE("%s: failed to get Binder constructor", __FUNCTION__);
		return NULL;
	}

	jobject obj = env->NewObject(cls, constr);
	if(!obj) {
		LOGE("%s: failed to create a Binder object", __FUNCTION__);
		return NULL;
	}
	jfieldID field  = env->GetFieldID(cls,"mObject","I");
	if(!field){
		LOGE("%s: failed to get native binder holder");
		return NULL;
	}

	//trying to replace the binder field of the method
	android::IBinder * ref = new android::HelloWorldService();
	env->SetIntField(obj,field,(int)ref);
	return obj;
}
