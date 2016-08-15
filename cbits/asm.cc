#include <stdio.h>
#include <jni.h>
#include "asm.h"

void createJvm(void** jvm, void** env, char* optionStr) {
  JavaVMInitArgs vm_args;
  JavaVMOption* options = new JavaVMOption[1];
  options[0].optionString = optionStr;
  vm_args.version = JNI_VERSION_1_8;
  vm_args.nOptions = 1;
  vm_args.options = options;
  vm_args.ignoreUnrecognized = false;
  JNI_CreateJavaVM((JavaVM**)jvm, env, &vm_args);
  delete options;
}

void assemble(JNIEnv *env, int argc, char **argv) {
  jclass cls = env->FindClass("mmhelloworld/idrisjvmruntime/AssemblerRunner");
  jmethodID mainMethodId = env->GetStaticMethodID(cls, "main", "([Ljava/lang/String;)V");

  jobjectArray jargs = env->NewObjectArray(1, env->FindClass("java/lang/String"), 0);

  for (int i = 0; i < argc; i++) {
    jstring str = env->NewStringUTF(argv[i]);
    env->SetObjectArrayElement(jargs, i, str);
  }

  env->CallStaticVoidMethod(cls, mainMethodId, jargs);
}

void destroyJvm(JavaVM *jvm) {
  jvm->DestroyJavaVM();
}