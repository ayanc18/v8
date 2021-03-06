// Copyright 2015 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_INSPECTOR_PUBLIC_V8INSPECTORCLIENT_H_
#define V8_INSPECTOR_PUBLIC_V8INSPECTORCLIENT_H_

#include "src/inspector/public/StringBuffer.h"
#include "src/inspector/public/StringView.h"

#include <v8.h>

namespace v8_inspector {

class V8StackTrace;

enum class V8ConsoleAPIType { kClear, kDebug, kLog, kInfo, kWarning, kError };

class PLATFORM_EXPORT V8InspectorClient {
 public:
  virtual ~V8InspectorClient() {}

  virtual void runMessageLoopOnPause(int contextGroupId) {}
  virtual void quitMessageLoopOnPause() {}
  virtual void runIfWaitingForDebugger(int contextGroupId) {}

  virtual void muteMetrics(int contextGroupId) {}
  virtual void unmuteMetrics(int contextGroupId) {}

  virtual void beginUserGesture() {}
  virtual void endUserGesture() {}

  virtual std::unique_ptr<StringBuffer> valueSubtype(v8::Local<v8::Value>) {
    return nullptr;
  }
  virtual bool formatAccessorsAsProperties(v8::Local<v8::Value>) {
    return false;
  }
  virtual bool isInspectableHeapObject(v8::Local<v8::Object>) { return true; }

  virtual v8::Local<v8::Context> ensureDefaultContextInGroup(
      int contextGroupId) {
    return v8::Local<v8::Context>();
  }
  virtual void beginEnsureAllContextsInGroup(int contextGroupId) {}
  virtual void endEnsureAllContextsInGroup(int contextGroupId) {}

  virtual void installAdditionalCommandLineAPI(v8::Local<v8::Context>,
                                               v8::Local<v8::Object>) {}
  virtual void consoleAPIMessage(int contextGroupId, V8ConsoleAPIType,
                                 const StringView& message,
                                 const StringView& url, unsigned lineNumber,
                                 unsigned columnNumber, V8StackTrace*) {}
  virtual v8::MaybeLocal<v8::Value> memoryInfo(v8::Isolate*,
                                               v8::Local<v8::Context>) {
    return v8::MaybeLocal<v8::Value>();
  }

  virtual void consoleTime(const StringView& title) {}
  virtual void consoleTimeEnd(const StringView& title) {}
  virtual void consoleTimeStamp(const StringView& title) {}
  virtual double currentTimeMS() { return 0; }
  typedef void (*TimerCallback)(void*);
  virtual void startRepeatingTimer(double, TimerCallback, void* data) {}
  virtual void cancelTimer(void* data) {}

  // TODO(dgozman): this was added to support service worker shadow page. We
  // should not connect at all.
  virtual bool canExecuteScripts(int contextGroupId) { return true; }
};

}  // namespace v8_inspector

#endif  // V8_INSPECTOR_PUBLIC_V8INSPECTORCLIENT_H_
