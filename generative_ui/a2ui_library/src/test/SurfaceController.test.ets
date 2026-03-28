/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium';
import { 
  SurfaceController, 
  SurfaceErrorType, 
  SurfaceEventType,
  ActionReceiver,
  ErrorCallback,
  SurfaceEventCallback
} from '../main/ets/engine/core/SurfaceController';
import { Catalog } from '../main/ets/engine/core/Catalog';
import { A2UIMessageType } from '../main/ets/engine/core/A2UIMessage';

export default function SurfaceControllerUnitTest() {
  describe('SurfaceControllerTest', () => {
    describe('Constructor', () => {
      it('should_create_controller_with_catalog_and_callback', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        
        let controller = new SurfaceController(catalog, eventCallback);
        
        expect(controller !== null).assertTrue();
        expect(controller !== undefined).assertTrue();
      });

      it('should_create_controller_with_schema_check_enabled', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        
        let controller = new SurfaceController(catalog, eventCallback, true);
        
        expect(controller !== null).assertTrue();
      });

      it('should_create_controller_with_schema_check_disabled', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        
        let controller = new SurfaceController(catalog, eventCallback, false);
        
        expect(controller !== null).assertTrue();
      });

      it('should_create_controller_with_catalog_id', 0, () => {
        let catalog = new Catalog('https://example.com/catalog.json', []);
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        
        let controller = new SurfaceController(catalog, eventCallback);
        
        expect(controller !== null).assertTrue();
      });
    });

    describe('RegisterActionReceiver', () => {
      it('should_register_action_receiver_successfully', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let controller = new SurfaceController(catalog, eventCallback);
        
        let actionReceiver: ActionReceiver = (action: string) => {};
        
        controller.registerActionReceiver(actionReceiver);
      });

      it('should_register_different_action_receivers', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let controller = new SurfaceController(catalog, eventCallback);
        
        let receiver1: ActionReceiver = (action: string) => {};
        let receiver2: ActionReceiver = (action: string) => {};
        
        controller.registerActionReceiver(receiver1);
        controller.registerActionReceiver(receiver2);
      });
    });

    describe('RegisterErrorCallback', () => {
      it('should_register_error_callback_successfully', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let controller = new SurfaceController(catalog, eventCallback);
        
        let errorCallback: ErrorCallback = (code, errorMsg) => {};
        
        controller.registerErrorCallback(errorCallback);
      });

      it('should_register_different_error_callbacks', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let controller = new SurfaceController(catalog, eventCallback);
        
        let callback1: ErrorCallback = (code, errorMsg) => {};
        let callback2: ErrorCallback = (code, errorMsg) => {};
        
        controller.registerErrorCallback(callback1);
        controller.registerErrorCallback(callback2);
      });
    });

    describe('EventNotification', () => {
      it('should_notify_surface_created_event', 0, () => {
        let catalog = Catalog.basic();
        let receivedEventType: SurfaceEventType = SurfaceEventType.UNKNOWN;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {
          receivedEventType = eventType;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback((code, msg) => {});
        
        let dsl = '{"version":"v0.9","createSurface":{"surfaceId":"main","catalogId":"catalog"}}';
        controller.onReceive(dsl);
        
        expect(receivedEventType).assertEqual(SurfaceEventType.SURFACE_CREATED);
      });

      it('should_notify_surface_components_updated_event', 0, () => {
        let catalog = Catalog.basic();
        let receivedEventType: SurfaceEventType = SurfaceEventType.UNKNOWN;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {
          receivedEventType = eventType;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback((code, msg) => {});
        
        let dsl = '{"version":"v0.9","updateComponents":{"surfaceId":"main","components":[]}}';
        controller.onReceive(dsl);
        
        expect(receivedEventType).assertEqual(SurfaceEventType.SURFACE_COMPONENTS_UPDATED);
      });

      it('should_notify_surface_data_model_updated_event', 0, () => {
        let catalog = Catalog.basic();
        let receivedEventType: SurfaceEventType = SurfaceEventType.UNKNOWN;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {
          receivedEventType = eventType;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback((code, msg) => {});
        
        let dsl = '{"version":"v0.9","updateDataModel":{"surfaceId":"main","value":{}}}';
        controller.onReceive(dsl);
        
        expect(receivedEventType).assertEqual(SurfaceEventType.SURFACE_DATA_MODEL_UPDATED);
      });

      it('should_notify_surface_deleted_event', 0, () => {
        let catalog = Catalog.basic();
        let receivedEventType: SurfaceEventType = SurfaceEventType.UNKNOWN;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {
          receivedEventType = eventType;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback((code, msg) => {});
        
        let dsl = '{"version":"v0.9","deleteSurface":{"surfaceId":"main"}}';
        controller.onReceive(dsl);
        
        expect(receivedEventType).assertEqual(SurfaceEventType.SURFACE_DELETED);
      });

      it('should_not_notify_event_when_callback_is_undefined', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = undefined as any;
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback((code, msg) => {});
        
        let dsl = '{"version":"v0.9","createSurface":{"surfaceId":"main"}}';
        controller.onReceive(dsl);
      });
    });

    describe('ErrorHandling', () => {
      it('should_call_error_callback_when_invalid_json', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let receivedErrorCode: SurfaceErrorType = SurfaceErrorType.NO_ERROR;
        let receivedErrorMsg: string = '';
        let errorCallback: ErrorCallback = (code, errorMsg) => {
          receivedErrorCode = code;
          receivedErrorMsg = errorMsg;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback(errorCallback);
        
        controller.onReceive('invalid json');
        
        expect(receivedErrorCode).assertEqual(SurfaceErrorType.ERROR_NO_SURFACE_MATCHED);
        expect(receivedErrorMsg).assertEqual('dsl message parse failed');
      });

      it('should_call_error_callback_when_empty_string', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let receivedErrorCode: SurfaceErrorType = SurfaceErrorType.NO_ERROR;
        let errorCallback: ErrorCallback = (code, errorMsg) => {
          receivedErrorCode = code;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback(errorCallback);
        
        controller.onReceive('');
        
        expect(receivedErrorCode).assertEqual(SurfaceErrorType.ERROR_NO_SURFACE_MATCHED);
      });

      it('should_call_error_callback_when_missing_version', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let receivedErrorCode: SurfaceErrorType = SurfaceErrorType.NO_ERROR;
        let errorCallback: ErrorCallback = (code, errorMsg) => {
          receivedErrorCode = code;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback(errorCallback);
        
        let dsl = '{"createSurface":{"surfaceId":"main"}}';
        controller.onReceive(dsl);
        
        expect(receivedErrorCode).assertEqual(SurfaceErrorType.ERROR_NO_SURFACE_MATCHED);
      });

      it('should_call_error_callback_when_unknown_message_type', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let receivedErrorCode: SurfaceErrorType = SurfaceErrorType.NO_ERROR;
        let errorCallback: ErrorCallback = (code, errorMsg) => {
          receivedErrorCode = code;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback(errorCallback);
        
        let dsl = '{"version":"v0.9","unknownType":{"surfaceId":"main"}}';
        controller.onReceive(dsl);
        
        expect(receivedErrorCode).assertEqual(SurfaceErrorType.ERROR_NO_SURFACE_MATCHED);
      });

      it('should_call_error_callback_when_missing_surfaceId', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let receivedErrorCode: SurfaceErrorType = SurfaceErrorType.NO_ERROR;
        let errorCallback: ErrorCallback = (code, errorMsg) => {
          receivedErrorCode = code;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback(errorCallback);
        
        let dsl = '{"version":"v0.9","createSurface":{}}';
        controller.onReceive(dsl);
        
        expect(receivedErrorCode).assertEqual(SurfaceErrorType.ERROR_NO_SURFACE_MATCHED);
      });

      it('should_not_call_error_callback_when_no_error_callback_registered', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let controller = new SurfaceController(catalog, eventCallback);
        
        controller.onReceive('invalid json');
      });
    });

    describe('OnReceive', () => {
      it('should_handle_create_surface_message', 0, () => {
        let catalog = Catalog.basic();
        let receivedEventType: SurfaceEventType = SurfaceEventType.UNKNOWN;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {
          receivedEventType = eventType;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback((code, msg) => {});
        
        let dsl = '{"version":"v0.9","createSurface":{"surfaceId":"test-surface","catalogId":"test-catalog"}}';
        controller.onReceive(dsl);
        
        expect(receivedEventType).assertEqual(SurfaceEventType.SURFACE_CREATED);
      });

      it('should_handle_update_components_message', 0, () => {
        let catalog = Catalog.basic();
        let receivedEventType: SurfaceEventType = SurfaceEventType.UNKNOWN;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {
          receivedEventType = eventType;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback((code, msg) => {});
        
        let dsl = '{"version":"v0.9","updateComponents":{"surfaceId":"main","components":[{"id":"text1","component":"Text","text":"Hello"}]}}';
        controller.onReceive(dsl);
        
        expect(receivedEventType).assertEqual(SurfaceEventType.SURFACE_COMPONENTS_UPDATED);
      });

      it('should_handle_update_data_model_message', 0, () => {
        let catalog = Catalog.basic();
        let receivedEventType: SurfaceEventType = SurfaceEventType.UNKNOWN;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {
          receivedEventType = eventType;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback((code, msg) => {});
        
        let dsl = '{"version":"v0.9","updateDataModel":{"surfaceId":"main","value":{"count":42}}}';
        controller.onReceive(dsl);
        
        expect(receivedEventType).assertEqual(SurfaceEventType.SURFACE_DATA_MODEL_UPDATED);
      });

      it('should_handle_delete_surface_message', 0, () => {
        let catalog = Catalog.basic();
        let receivedEventType: SurfaceEventType = SurfaceEventType.UNKNOWN;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {
          receivedEventType = eventType;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback((code, msg) => {});
        
        let dsl = '{"version":"v0.9","deleteSurface":{"surfaceId":"main"}}';
        controller.onReceive(dsl);
        
        expect(receivedEventType).assertEqual(SurfaceEventType.SURFACE_DELETED);
      });

      it('should_handle_multiple_sequential_messages', 0, () => {
        let catalog = Catalog.basic();
        let eventTypes: SurfaceEventType[] = [];
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {
          eventTypes.push(eventType);
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback((code, msg) => {});
        
        controller.onReceive('{"version":"v0.9","createSurface":{"surfaceId":"main"}}');
        controller.onReceive('{"version":"v0.9","updateComponents":{"surfaceId":"main","components":[]}}');
        controller.onReceive('{"version":"v0.9","updateDataModel":{"surfaceId":"main","value":{}}}');
        controller.onReceive('{"version":"v0.9","deleteSurface":{"surfaceId":"main"}}');
        
        expect(eventTypes.length).assertEqual(4);
        expect(eventTypes[0]).assertEqual(SurfaceEventType.SURFACE_CREATED);
        expect(eventTypes[1]).assertEqual(SurfaceEventType.SURFACE_COMPONENTS_UPDATED);
        expect(eventTypes[2]).assertEqual(SurfaceEventType.SURFACE_DATA_MODEL_UPDATED);
        expect(eventTypes[3]).assertEqual(SurfaceEventType.SURFACE_DELETED);
      });

      it('should_handle_json_with_whitespace', 0, () => {
        let catalog = Catalog.basic();
        let receivedEventType: SurfaceEventType = SurfaceEventType.UNKNOWN;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {
          receivedEventType = eventType;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback((code, msg) => {});
        
        let dsl = '{ "version" : "v0.9" , "createSurface" : { "surfaceId" : "main" } }';
        controller.onReceive(dsl);
        
        expect(receivedEventType).assertEqual(SurfaceEventType.SURFACE_CREATED);
      });
    });

    describe('SurfaceErrorTypeEnum', () => {
      it('should_have_correct_error_type_values', 0, () => {
        expect(SurfaceErrorType.NO_ERROR).assertEqual(0);
        expect(SurfaceErrorType.ERROR_NO_SURFACE_MATCHED).assertEqual(1);
      });
    });

    describe('SurfaceEventTypeEnum', () => {
      it('should_have_correct_event_type_values', 0, () => {
        expect(SurfaceEventType.UNKNOWN).assertEqual(-1);
        expect(SurfaceEventType.SURFACE_CREATED).assertEqual(0);
        expect(SurfaceEventType.SURFACE_COMPONENTS_UPDATED).assertEqual(1);
        expect(SurfaceEventType.SURFACE_DATA_MODEL_UPDATED).assertEqual(2);
        expect(SurfaceEventType.SURFACE_DELETED).assertEqual(3);
      });
    });

    describe('EdgeCases', () => {
      it('should_handle_null_json', 0, () => {
        let catalog = Catalog.basic();
        let receivedErrorCode: SurfaceErrorType = SurfaceErrorType.NO_ERROR;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let errorCallback: ErrorCallback = (code, errorMsg) => {
          receivedErrorCode = code;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback(errorCallback);
        
        controller.onReceive('null');
        
        expect(receivedErrorCode).assertEqual(SurfaceErrorType.ERROR_NO_SURFACE_MATCHED);
      });

      it('should_handle_json_array', 0, () => {
        let catalog = Catalog.basic();
        let receivedErrorCode: SurfaceErrorType = SurfaceErrorType.NO_ERROR;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let errorCallback: ErrorCallback = (code, errorMsg) => {
          receivedErrorCode = code;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback(errorCallback);
        
        controller.onReceive('[]');
        
        expect(receivedErrorCode).assertEqual(SurfaceErrorType.ERROR_NO_SURFACE_MATCHED);
      });

      it('should_handle_empty_json_object', 0, () => {
        let catalog = Catalog.basic();
        let receivedErrorCode: SurfaceErrorType = SurfaceErrorType.NO_ERROR;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let errorCallback: ErrorCallback = (code, errorMsg) => {
          receivedErrorCode = code;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback(errorCallback);
        
        controller.onReceive('{}');
        
        expect(receivedErrorCode).assertEqual(SurfaceErrorType.ERROR_NO_SURFACE_MATCHED);
      });

      it('should_handle_whitespace_only_string', 0, () => {
        let catalog = Catalog.basic();
        let receivedErrorCode: SurfaceErrorType = SurfaceErrorType.NO_ERROR;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let errorCallback: ErrorCallback = (code, errorMsg) => {
          receivedErrorCode = code;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback(errorCallback);
        
        controller.onReceive('   ');
        
        expect(receivedErrorCode).assertEqual(SurfaceErrorType.ERROR_NO_SURFACE_MATCHED);
      });

      it('should_handle_unclosed_json_object', 0, () => {
        let catalog = Catalog.basic();
        let receivedErrorCode: SurfaceErrorType = SurfaceErrorType.NO_ERROR;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let errorCallback: ErrorCallback = (code, errorMsg) => {
          receivedErrorCode = code;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback(errorCallback);
        
        controller.onReceive('{"version":"v0.9"');
        
        expect(receivedErrorCode).assertEqual(SurfaceErrorType.ERROR_NO_SURFACE_MATCHED);
      });

      it('should_handle_version_null', 0, () => {
        let catalog = Catalog.basic();
        let receivedErrorCode: SurfaceErrorType = SurfaceErrorType.NO_ERROR;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let errorCallback: ErrorCallback = (code, errorMsg) => {
          receivedErrorCode = code;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback(errorCallback);
        
        let dsl = '{"version":null,"createSurface":{"surfaceId":"main"}}';
        controller.onReceive(dsl);
        
        expect(receivedErrorCode).assertEqual(SurfaceErrorType.ERROR_NO_SURFACE_MATCHED);
      });

      it('should_handle_special_characters_in_surfaceId', 0, () => {
        let catalog = Catalog.basic();
        let receivedEventType: SurfaceEventType = SurfaceEventType.UNKNOWN;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {
          receivedEventType = eventType;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback((code, msg) => {});
        
        let dsl = '{"version":"v0.9","createSurface":{"surfaceId":"test-surface_123"}}';
        controller.onReceive(dsl);
        
        expect(receivedEventType).assertEqual(SurfaceEventType.SURFACE_CREATED);
      });

      it('should_handle_unicode_in_surfaceId', 0, () => {
        let catalog = Catalog.basic();
        let receivedEventType: SurfaceEventType = SurfaceEventType.UNKNOWN;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {
          receivedEventType = eventType;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback((code, msg) => {});
        
        let dsl = '{"version":"v0.9","createSurface":{"surfaceId":"主界面"}}';
        controller.onReceive(dsl);
        
        expect(receivedEventType).assertEqual(SurfaceEventType.SURFACE_CREATED);
      });
    });

    describe('CallbackValidation', () => {
      it('should_pass_correct_controller_instance_in_event_callback', 0, () => {
        let catalog = Catalog.basic();
        let receivedController: SurfaceController | null = null;
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {
          receivedController = controller;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback((code, msg) => {});
        
        let dsl = '{"version":"v0.9","createSurface":{"surfaceId":"main"}}';
        controller.onReceive(dsl);
        
        expect(receivedController !== null).assertTrue();
        expect(receivedController === controller).assertTrue();
      });

      it('should_receive_correct_error_code_type', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let receivedCode: SurfaceErrorType | null = null;
        let errorCallback: ErrorCallback = (code, errorMsg) => {
          receivedCode = code;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback(errorCallback);
        
        controller.onReceive('invalid json');
        
        expect(receivedCode !== null).assertTrue();
        expect(typeof receivedCode).assertEqual('number');
      });

      it('should_receive_correct_error_message_type', 0, () => {
        let catalog = Catalog.basic();
        let eventCallback: SurfaceEventCallback = (eventType, controller) => {};
        let receivedMsg: string | null = null;
        let errorCallback: ErrorCallback = (code, errorMsg) => {
          receivedMsg = errorMsg;
        };
        let controller = new SurfaceController(catalog, eventCallback);
        controller.registerErrorCallback(errorCallback);
        
        controller.onReceive('invalid json');
        
        expect(receivedMsg !== null).assertTrue();
        expect(typeof receivedMsg).assertEqual('string');
      });
    });
  });
}
