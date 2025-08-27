/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import "UIKit/UIKit.h"
#import <Foundation/Foundation.h>

#include "engine.h"
#include <string>
#include <algorithm>

@interface KoalaView : UIView<UITextInput, UIKeyInput>

    -(bool)showScreenKeyboard;
    -(bool)hideScreenKeyboard;
    -(void)cleanEnteredText;

    -(void)pressesBegan:(NSSet<UIPress*>*)pressees withEvent:(UIPressesEvent*)event;
    -(void)pressesEnded:(NSSet<UIPress*>*)pressees withEvent:(UIPressesEvent*)event;
    -(void)touchesBegan:(NSSet<UITouch*>*)touches withEvent:(UIEvent*)event;
    -(void)touchesEnded:(NSSet<UITouch*>*)touches withEvent:(UIEvent*)event;
    -(void)touchesMoved:(NSSet<UITouch*>*)touches withEvent:(UIEvent*)event;
    -(void)touchesCancelled:(NSSet<UITouch*>*)touches withEvent:(UIEvent*)event;
    -(void)onResize:(int)width  withHeight:(int)height;

    -(IosEngine*)engine;
    -(void)setEngine:(IosEngine*)engine;
    -(void)setWorkArea:(CGRect)workArea;

    @property id<UITextInputDelegate> _inputDelegate;
    @property UIKeyboardType currentKeyboardType;
    @property UIKeyboardAppearance currentKeyboardAppearance;
    @property UIReturnKeyType currentReturnKeyType;
    @property UITextAutocapitalizationType currentAutocapitalizationType;
    @property UITextAutocorrectionType currentAutocorrectionType;

    @property NSMutableString* enteredText;
    @property UITextRange* enteredRange;

    @property CGRect _workArea;
    @property (nonatomic, copy) NSDictionary *markedTextStyle;
@end

typedef enum KeyEventType  {
    COMPOSE,
    COMMIT
} KeyEventType;

typedef enum KeyActionType {
    UP,
    DOWN
} KeyActionType;

@interface IntermediateTextPosition : UITextPosition

    -(instancetype)init:(NSInteger)position;
    -(NSInteger)pos;

    @property NSInteger _position;

@end

@interface IntermediateTextRange : UITextRange

    -(instancetype)init:(IntermediateTextPosition*)start withEnd:(IntermediateTextPosition*)end;
    -(UITextPosition*)start;
    -(UITextPosition*)end;
    -(BOOL)isEmpty;

    @property IntermediateTextPosition* _start;
    @property IntermediateTextPosition* _end;

@end

void skoala_startJS(/* KoalaView*/ void*, const char*);