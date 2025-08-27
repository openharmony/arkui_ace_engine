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

#import "koala-view.h"
#import "engine.h"

@implementation KoalaView 

    @synthesize _inputDelegate;
    @synthesize currentKeyboardType = UIKeyboardTypeDefault;
    @synthesize currentKeyboardAppearance = UIKeyboardAppearenceDefault;
    @synthesize currentReturnKeyType = UIReturnKeyDefault;
    @synthesize currentAutocapitalizationType = UITextAutocapitalizationTypeSentences;
    @synthesize currentAutocorrectionType = UITextAutocorrectionTypeYes;
    @synthesize markedTextStyle;

    IosEngine* _engine = nullptr;

    -(IosEngine*)engine {
        return _engine;
    }

    -(instancetype)initWithFrame:(CGRect)frame {
        self = [super initWithFrame:frame];
        self.multipleTouchEnabled = true;
        self.enteredText = [[NSMutableString alloc]init];
        UIHoverGestureRecognizer *hover = [[UIHoverGestureRecognizer alloc] initWithTarget:self action:@selector(hovering)];
        [self addGestureRecognizer: hover];
        return self;
    }

    -(void)hovering:(UIHoverGestureRecognizer*)recognizer {
        // TODO: check when ios will works
        CGPoint point = [recognizer locationInView: self];
        _engine->setMousePoint(point);
    }

    -(void)setEngine:(IosEngine*)engine {
        _engine = engine;
    }

    -(void)setWorkArea:(CGRect)workArea {
        self._workArea = workArea;
    }

    -(BOOL)canBecomeFirstResponder {
        return YES;
    }

    -(bool)showScreenKeyboard {
        return [self becomeFirstResponder];
    }

    -(bool)hideScreenKeyboard {
        [self cleanEnteredText];
        return [self resignFirstResponder];
    }
    -(void)cleanEnteredText {
        [self.enteredText setString:@""];
    }

    -(void)pressesBegan:(NSSet<UIPress*>*)pressees withEvent:(UIPressesEvent*)event {
        [super pressesBegan:pressees withEvent:event];
    }
    -(void)pressesEnded:(NSSet<UIPress*>*)pressees withEvent:(UIPressesEvent*)event {
        [super pressesEnded:pressees withEvent:event];
    }
    -(void)touchesBegan:(NSSet<UITouch*>*)touches withEvent:(UIEvent*)event {
        if (_engine)
            _engine->addTouchesEvent(touches, 1, self, self._workArea);
    }
    -(void)touchesEnded:(NSSet<UITouch*>*)touches withEvent:(UIEvent*)event {
        if (_engine)
            _engine->addTouchesEvent(touches, 2, self, self._workArea);        
    }
    -(void)touchesMoved:(NSSet<UITouch*>*)touches withEvent:(UIEvent*)event {
        if (_engine)
            _engine->addTouchesEvent(touches, 3, self, self._workArea);
    }
    -(void)touchesCancelled:(NSSet<UITouch*>*)touches withEvent:(UIEvent*)event {
        if (_engine)
            _engine->addTouchesEvent(touches, 4, self, self._workArea);
    }
    -(void)onResize:(int)width  withHeight:(int)height {
        if (_engine)
            _engine->onResize(width, height);
    }

    /* TextInput */
    -(UIView*)textInputView {
        return self;
    }
    -(id<UITextInputDelegate>)inputDelegate {
        return _inputDelegate;
    }
    -(void)setInputDelegate:(id<UITextInputDelegate>)delegate {
        self._inputDelegate = delegate;
    }
    -(UITextRange*)markedTextRange {
        return self.enteredRange;
    }
    -(void)setMarkedText:(NSString*)markedText selectedRange:(NSRange)selectedRange {
        /* TODO: unused */
        return;
    }
    -(void)replaceRange:(UITextRange*)range withText:(NSString*)text {
 
        [self cleanEnteredText];
        [self.enteredText appendString:text];
        _engine->peer->callOnTextInput(KeyEventType::COMMIT, 0, std::string([self.enteredText UTF8String]));
        _engine->peer->callOnTextInput(KeyEventType::COMMIT, 0, std::string(" "));
        [self cleanEnteredText];
  
        return;
    }
    -(UITextRange*)selectedTextRange {
        return self.enteredRange;
    }
    -(void)setSelectedTextRange:(UITextRange*)selectedTextRange {
        self.enteredRange = selectedTextRange;
        return;
    }
    -(BOOL)shouldChangeTextInRange:(UITextRange*)range replacementText:(NSString*)text {
        /* Here we should decide to replace text in range or not */
        return YES;
    }
    -(NSString*)textInRange:(UITextRange*)range {
        /*
        NSInteger start = reinterpret_cast<IntermediateTextPosition*>([range start]).pos;
        NSInteger end = reinterpret_cast<IntermediateTextPosition*>([range end]).pos;
        */
        /* TODO: change range */
        return self.enteredText;
    }
    -(UITextPosition*)positionFromPosition:(UITextPosition*)position offset:(NSInteger)offset {
        NSInteger p = reinterpret_cast<IntermediateTextPosition*>(position).pos;
        UITextPosition* end = self.endOfDocument;
        if (end != nil) {
            return [[IntermediateTextPosition alloc]init:std::max(std::min(p + offset, reinterpret_cast<IntermediateTextPosition*>(end).pos), NSInteger(0))];
        } else {
            return nil;
        }
    }
    -(UITextPosition*)positionFromPosition:(UITextPosition*)position inDirection:(UITextLayoutDirection)direction offset:(NSInteger)offset {
        /* TODO: unused */
        return nil;
    }
    -(UITextRange*)textRangeFromPosition:(UITextPosition*)fromPosition toPosition:(UITextPosition*)toPosition {
        NSInteger from = reinterpret_cast<IntermediateTextPosition*>(fromPosition).pos;
        NSInteger to = reinterpret_cast<IntermediateTextPosition*>(toPosition).pos;
        
        IntermediateTextPosition* min = [[IntermediateTextPosition alloc]init:std::min(from, to)];
        IntermediateTextPosition* max = [[IntermediateTextPosition alloc]init:std::max(from, to)];

        return [[IntermediateTextRange alloc]init:min withEnd:max];
    }
    -(UITextPosition*)positionWithinRange:(UITextRange*)range farthestInDirection:(UITextLayoutDirection)direction {
        /* TODO: unused */
        return nil;
    }
    -(CGRect)firstRectForRange:(UITextRange*)range {
        /* TODO: unused */
        return CGRectMake(0,0,0,0);
    }
    -(UITextPosition*)closestPositionToPoint:(CGPoint)point {
        /* TODO: unused */
        return nil;
    }
    -(UITextPosition*)closestPositionToPoint:(CGPoint)point withinRange:(UITextRange*)range {
        /* TODO: unused */
        return nil;
    }
    -(CGRect)caretRectForPosition:(UITextPosition*)position {
        /* TODO: unused */
        return CGRectMake(0,0,0,0);
    }
    -(NSArray<UITextSelectionRect*>*)selectionRectsForRange:(UITextRange*)range {
        /* TODO: unused */
        return nil;
    }
    -(UITextRange*)characterRangeAtPoint:(CGPoint)point {
        /* TODO: unused */
        return nil;
    }
    -(UITextPosition*)beginningOfDocument {
        return [[IntermediateTextPosition alloc]init:0];
    }
    -(UITextPosition*)endOfDocument {
        IntermediateTextPosition* pos = [[IntermediateTextPosition alloc]init:self.enteredText.length];
        return pos;
    }
    -(NSComparisonResult)comparePosition:(UITextPosition*)position toPosition:(UITextPosition*)other {
        NSInteger from = reinterpret_cast<IntermediateTextPosition*>(position).pos;
        NSInteger to = reinterpret_cast<IntermediateTextPosition*>(other).pos;
        if (from < to) {
            return NSOrderedAscending;
        } else if (from > to) {
            return NSOrderedDescending;
        } else {
            return NSOrderedSame;
        }
    }
    -(NSInteger)offsetFromPosition:(UITextPosition*)from toPosition:(UITextPosition*)toPosition {
        /* TODO: unused */
        return 0;
    }
    -(NSWritingDirection)baseWritingDirectionForPosition:(UITextPosition*)position inDirection:(UITextStorageDirection)direction {
        return NSWritingDirectionLeftToRight;
    }
    -(void)setBaseWritingDirection:(NSWritingDirection)writingDirection forRange:(UITextRange*)range {
        /* TODO: unused */
        return;
    }
    -(UITextRange*)characterRangeByExtendingPosition:(UITextPosition*)position inDirection:(UITextLayoutDirection)direction {
        /* TODO: unused */
        return nil;
    }
    -(void)unmarkText {
        /* TODO: unused */
        return;
    }
    -(id<UITextInputTokenizer>)tokenizer {
        return [[UITextInputStringTokenizer alloc]init];
    }
    -(UIKeyboardType)keyboardType {
        return self.currentKeyboardType;
    }
    -(UIKeyboardAppearance)keyboardAppearance {
        return self.currentKeyboardAppearance;
    }
    -(UIReturnKeyType)returnKeyType {
        return self.currentReturnKeyType;
    }
    -(UITextAutocapitalizationType)autocapitalizationType {
        return self.currentAutocapitalizationType;
    }
    -(UITextAutocorrectionType)autocorrectionType {
        return self.currentAutocorrectionType;
    }

    /* TextInput Delegate */
    -(void)textWillChange {
        [_inputDelegate textWillChange:self];
    }
    -(void)textDidChange {
        [_inputDelegate textDidChange:self];
    }
    -(void)selectionWillChange {
        [_inputDelegate selectionWillChange:self];
    }
    -(void)selectionDidChange {
        [_inputDelegate selectionDidChange:self];
    }

    /* KeyInput */
    -(BOOL)hasText {
        if([self.enteredText length] != 0) {
            return YES;
        } else {
            return NO;
        }
    }
    -(void)insertText:(NSString*)text {

        [self.enteredText appendString:text];

        IntermediateTextPosition* start = [[IntermediateTextPosition alloc]init:0];
        IntermediateTextPosition* end = [[IntermediateTextPosition alloc]init:self.enteredText.length];
        IntermediateTextRange* range = [[IntermediateTextRange alloc]init:start withEnd:end];
        self.enteredRange = range; 

        _engine->peer->callOnTextInput(KeyEventType::COMPOSE, 0, std::string([self.enteredText UTF8String]));

        if([text isEqualToString:@" "]) { // Key Space
            _engine->peer->callOnTextInput(KeyEventType::COMMIT, 0, std::string([self.enteredText UTF8String]));
            [self cleanEnteredText];
        } else if ([text isEqualToString:@"\n"]) { // Key Enter (for multiline TextField)
            _engine->peer->callOnKey(UIKeyboardHIDUsageKeyboardReturn, 0, KeyActionType::DOWN);
            [self cleanEnteredText];
        }
    }
    -(void)deleteBackward {
        if ([self.enteredText length] != 0) {
            [self.enteredText deleteCharactersInRange:NSMakeRange([self.enteredText length]-1, 1)];

            IntermediateTextPosition* start = [[IntermediateTextPosition alloc]init:0];
            IntermediateTextPosition* end = [[IntermediateTextPosition alloc]init:self.enteredText.length];
            IntermediateTextRange* range = [[IntermediateTextRange alloc]init:start withEnd:end];
            self.enteredRange = range; 

            _engine->peer->callOnTextInput(KeyEventType::COMPOSE, 0, std::string([self.enteredText UTF8String]));
        } else {
            _engine->peer->callOnKey(UIKeyboardHIDUsageKeyboardDeleteOrBackspace, 0, KeyActionType::DOWN);
        }
    }
@end

@implementation IntermediateTextPosition

    @synthesize _position;

    -(instancetype)init:(NSInteger)position {
        self = [super init];
        if(self) {
            self._position = position;
        }
        return self;
    }
    -(NSInteger)pos {
        return self._position;
    }

@end

@implementation IntermediateTextRange

    @synthesize _start;
    @synthesize _end;

    -(instancetype)init:(IntermediateTextPosition*)start withEnd:(IntermediateTextPosition*)end {
        self = [super init];
        if(self) {
            self._start = start;
            self._end = end;
        }
        return self;
    }
    -(UITextPosition*)start {
        return self._start;
    }
    -(UITextPosition*)end {
        return self._end;
    }
    -(BOOL)isEmpty {
        if (self._end.pos - self._start.pos <= 0) {
            return YES;
        } else {
            return NO;
        }
    }

@end