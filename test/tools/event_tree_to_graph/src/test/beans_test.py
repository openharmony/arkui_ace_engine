#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# Copyright (c) 2024 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

from src.beans.event_node import EventNode
from src.beans.event_procedures import EventProcedures
from src.beans.event_scope import EventScope
from src.beans.event_tree import EventTree
from src.beans.frame_node import FrameNode
from src.beans.procedure_step import ProcedureStep
from src.beans.state_history import StateHistory
from src.beans.touch_point import TouchPoint
from src.utils.log_wrapper import log_info, log_error


def test_begin(test_info):
    log_info("# " + test_info + " == test == begin")


def test_end(test_info, result):
    if result:
        log_info("# " + test_info + " == test PASSED == end")
    else:
        log_error("# " + test_info + " == test FAILED == end")


def test_frame_node():
    test_begin("test_frame_node")
    node_str = (" nodeId: 0, parentId: -1, tag: root, monopolizeEvents: 0, isHit: 1, hitTestMode: 0, responseRegion: "
                "RectT (0.00, 0.00) - [720.00 x 1280.00]\n")
    frame_node = FrameNode(node_str)
    frame_node.dump()
    test_end("test_frame_node", frame_node.is_succeed())


def test_touch_point():
    test_begin("test_touch_point")
    touch_point_str = (
        "id: 0, point: (123.12, 56.00), screenPoint: (45.00, 280.30), type: down, timestamp: 2017-08-25 15:00:22.295, "
        "isInjected: 0\n")
    touch_point = TouchPoint(touch_point_str)
    touch_point.dump()
    test_end("test_touch_point", touch_point.is_succeed())


def test_procedure_step():
    test_begin("test_procedure_step")
    procedure_step_str = "procedure: HandleTouchUp, timestamp: 2017-08-25 15:00:22.295"
    procedure_step = ProcedureStep(procedure_step_str)
    procedure_step.dump()
    test_end("test_procedure_step", procedure_step.is_succeed())


def test_state_history():
    test_begin("test_state_history")
    state_history = "stateHistory:\n" + \
                    "   procedure: HandleTouchDown, timestamp: 2017-08-20 15:00:22.247\n" + \
                    "   procedure: HandleTouchUp, timestamp: 2017-08-20 15:00:22.295\n"
    state_history = StateHistory(state_history)
    state_history.dump()
    test_end("test_state_history", state_history.is_succeed())


def test_event_node():
    test_begin("test_event_node")
    event_node_str = (
        "frameNodeId: 88, type: LongPressRecognizer, depth: 1, id: 0xef748aa0, parentId: 0xf063eed0, customInfo: "
        "duration: 500, isForDrag: 0, repeat: 0, fingers: 1\n"
        "stateHistory:\n"
        "   procedure: HandleTouchDown, timestamp: 2017-08-25 15:00:22.247\n"
        "   procedure: HandleTouchUp, timestamp: 2017-08-25 15:00:22.295\n")
    event_node = EventNode(event_node_str)
    event_node.dump()
    test_end("test_event_node", event_node.is_succeed())


def test_event_scope():
    test_begin("test_event_scope")
    event_scope_str = ("finger: 0\n"
                       "   frameNodeId: 0, type: root, depth: 0, id: 0, parentId: -1\n"
                       "   stateHistory:\n"
                       "      procedure: HandleTouchDown, timestamp: 2017-08-25 15:00:22.247\n"
                       "      procedure: HandleTouchUp, timestamp: 2017-08-25 15:00:22.295\n"
                       "   frameNodeId: 88, type: LongPressRecognizer, depth: 1, id: 0xef748aa0, parentId: "
                       "0xf063eed0, customInfo: duration: 500, isForDrag: 0, repeat: 0, fingers: 1\n"
                       "   stateHistory:\n"
                       "      procedure: HandleTouchDown, state: DETECTING, disposal: NONE, timestamp: 2017-08-25 "
                       "15:00:22.247\n"
                       "       procedure: HandleTouchUp, state: FAIL, disposal: REJECT, timestamp: 2017-08-25 "
                       "15:00:22.295\n")
    event_scope = EventScope(event_scope_str)
    event_scope.dump()
    test_end("test_event_scope", event_scope.is_succeed())


def test_event_procedures():
    test_begin("test_event_procedures")
    event_procedures_str = ("extra text\n"
                            "finger: 0\n"
                            "   frameNodeId: 0, type: root, depth: 0, id: 0, parentId: -1\n"
                            "   stateHistory:\n"
                            "      procedure: HandleTouchDown, timestamp: 2017-08-25 15:00:22.247\n"
                            "      procedure: HandleTouchUp, timestamp: 2017-08-25 15:00:22.295\n"
                            "   frameNodeId: 88, type: LongPressRecognizer, depth: 1, id: 0xef748aa0, parentId: "
                            "0xf063eed0, customInfo: duration: 500, isForDrag: 0, repeat: 0, fingers: 1\n"
                            "   stateHistory:\n"
                            "      procedure: HandleTouchDown, state: DETECTING, disposal: NONE, timestamp: 2017-08-25 "
                            "15:00:22.247\n"
                            "       procedure: HandleTouchUp, state: FAIL, disposal: REJECT, timestamp: 2017-08-25 "
                            "15:00:22.295\n"
                            "finger: 1\n"
                            "   frameNodeId: 22, type: root, depth: 0, id: 0, parentId: -1\n"
                            "   stateHistory:\n"
                            "      procedure: HandleTouchDown, timestamp: 2017-08-25 15:00:22.247\n"
                            "      procedure: HandleTouchUp, timestamp: 2017-08-25 15:00:22.295\n"
                            "   frameNodeId: 66, type: LongPressRecognizer, depth: 3, id: 0xef748aa0, parentId: "
                            "0xf063eed0, customInfo: duration: 500, isForDrag: 0, repeat: 0, fingers: 1\n"
                            "   stateHistory:\n"
                            "      procedure: HandleTouchDown, state: DETECTING, disposal: NONE, timestamp: 2017-08-25 "
                            "15:00:22.247\n"
                            "       procedure: HandleTouchUp, state: FAIL, disposal: REJECT, timestamp: 2017-08-25 "
                            "15:00:22.295\n"
                            "hello world")
    event_procedures = EventProcedures(event_procedures_str)
    event_procedures.dump()
    test_end("test_event_procedures", event_procedures.is_succeed())


def test_event_tree():
    test_begin("test_event_tree")
    event_tree_str = ("1: event tree =>\n"
                      " touch points:\n"
                      "  id: 0, point: Offset (288.00, 530.00), screenPoint: Offset (288.00, 530.00), "
                      "type: TouchDown, timestamp: 2017-08-25 15:00:22.043, isInjected: 0\n"
                      "  id: 0, point: Offset (288.00, 536.00), screenPoint: Offset (288.00, 536.00), type: TouchUp, "
                      "timestamp: 2017-08-25 15:00:22.130, isInjected: 0\n"
                      " hittest:\n"
                      "  nodeId: 0, parentId: -1, tag: root, monopolizeEvents: 0, isHit: 1, hitTestMode: 0, "
                      "responseRegion: RectT (0.00, 0.00) - [720.00 x 1280.00]\n"
                      "  nodeId: 1, parentId: 0, tag: stage, monopolizeEvents: 0, isHit: 1, hitTestMode: 0, "
                      "responseRegion: RectT (0.00, 0.00) - [720.00 x 1280.00]\n"
                      " event procedures:\n"
                      "  finger:0\n"
                      "   frameNodeId: 84, type: TouchEventActuator, depth: 0, id: 0xf072b240, parentId: 0x0\n"
                      "    stateHistory:\n"
                      "     procedure: HandleTouchDown, timestamp: 2017-08-25 15:00:22.046\n"
                      "     procedure: HandleTouchUp, timestamp: 2017-08-25 15:00:22.130\n"
                      "   frameNodeId: 84, type: ExclusiveRecognizer, depth: 0, id: 0xf063eed0, parentId: 0x0\n"
                      "    stateHistory:\n"
                      "     procedure: HandleTouchDown, state: READY, disposal: NONE, timestamp: 2017-08-25 "
                      "15:00:22.046\n"
                      "     procedure: HandleTouchUp, state: FAIL, disposal: REJECT, timestamp: 2017-08-25 "
                      "15:00:22.131\n"
                      "2: event tree =>\n")
    event_tree = EventTree(event_tree_str)
    event_tree.dump()
    test_end("test_event_tree", event_tree.is_succeed())


if __name__ == '__main__':
    test_frame_node()
    test_touch_point()
    test_procedure_step()
    test_state_history()
    test_event_node()
    test_event_scope()
    test_event_procedures()
    test_event_tree()
