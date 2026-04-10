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
  A2UIMessageType,
  A2UIMessage
} from '../main/ets/engine/core/A2UIMessage';

export default function A2UIMessageLocalUnitTest() {
  describe('A2UIMessageTest', () => {
    describe('Constructor', () => {
      it('should_create_message_with_all_properties', 0, () => {
        let body: ESObject = { catalogId: 'test-catalog' };
        let message = new A2UIMessage('v0.9', 'main', A2UIMessageType.CREATE_SURFACE, body);

        expect(message.version).assertEqual('v0.9');
        expect(message.surfaceId).assertEqual('main');
        expect(message.type).assertEqual(A2UIMessageType.CREATE_SURFACE);
        expect(message.messageBody).assertEqual('{"catalogId":"test-catalog"}');
      });

      it('should_create_message_with_undefined_body', 0, () => {
        let message = new A2UIMessage('v0.9', 'main', A2UIMessageType.DELETE_SURFACE, undefined);

        expect(message.version).assertEqual('v0.9');
        expect(message.surfaceId).assertEqual('main');
        expect(message.type).assertEqual(A2UIMessageType.DELETE_SURFACE);
        expect(message.messageBody === undefined).assertTrue();
      });

      it('should_create_message_with_empty_version', 0, () => {
        let message = new A2UIMessage('', 'main', A2UIMessageType.CREATE_SURFACE, undefined);

        expect(message.version).assertEqual('');
        expect(message.surfaceId).assertEqual('main');
      });

      it('should_create_message_with_empty_surfaceId', 0, () => {
        let message = new A2UIMessage('v0.9', '', A2UIMessageType.CREATE_SURFACE, undefined);

        expect(message.version).assertEqual('v0.9');
        expect(message.surfaceId).assertEqual('');
      });
    });

    describe('fromDSL_CreateSurface', () => {
      it('should_parse_create_surface_message', 0, () => {
        let dsl = '{"version":"v0.9","createSurface":{"surfaceId":"main","catalogId":"https://a2ui.org/catalog.json"}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.version).assertEqual('v0.9');
        expect(message?.surfaceId).assertEqual('main');
        expect(message?.type).assertEqual(A2UIMessageType.CREATE_SURFACE);
        expect(message?.messageBody).assertEqual('{"surfaceId":"main","catalogId":"https://a2ui.org/catalog.json"}');
      });

      it('should_parse_create_surface_with_minimal_fields', 0, () => {
        let dsl = '{"version":"v1.0","createSurface":{"surfaceId":"test"}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.version).assertEqual('v1.0');
        expect(message?.surfaceId).assertEqual('test');
      });

      it('should_return_null_when_create_surface_missing_surfaceId', 0, () => {
        let dsl = '{"version":"v0.9","createSurface":{"catalogId":"catalog"}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });

      it('should_parse_create_surface_with_empty_surfaceId', 0, () => {
        let dsl = '{"version":"v0.9","createSurface":{"surfaceId":""}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.surfaceId).assertEqual('');
      });
    });

    describe('fromDSL_UpdateComponents', () => {
      it('should_parse_update_components_message', 0, () => {
        let dsl = '{"version":"v0.9","updateComponents":{"surfaceId":"main","components":[{"id":"root","component":"Text"}]}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.version).assertEqual('v0.9');
        expect(message?.surfaceId).assertEqual('main');
        expect(message?.type).assertEqual(A2UIMessageType.UPDATE_COMPONENTS);
        expect(message?.messageBody).assertEqual('{"surfaceId":"main","components":[{"id":"root","component":"Text"}]}');
      });

      it('should_parse_update_components_with_empty_components_array', 0, () => {
        let dsl = '{"version":"v0.9","updateComponents":{"surfaceId":"main","components":[]}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.type).assertEqual(A2UIMessageType.UPDATE_COMPONENTS);
      });

      it('should_parse_update_components_with_multiple_components', 0, () => {
        let dsl = '{"version":"v0.9","updateComponents":{"surfaceId":"main","components":[{"id":"row1","component":"Row"},{"id":"text1","component":"Text","text":"Hello"}]}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.type).assertEqual(A2UIMessageType.UPDATE_COMPONENTS);
      });

      it('should_return_null_when_update_components_missing_surfaceId', 0, () => {
        let dsl = '{"version":"v0.9","updateComponents":{"components":[]}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });
    });

    describe('fromDSL_UpdateDataModel', () => {
      it('should_parse_update_data_model_message', 0, () => {
        let dsl = '{"version":"v0.9","updateDataModel":{"surfaceId":"main","value":{"name":"test"}}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.version).assertEqual('v0.9');
        expect(message?.surfaceId).assertEqual('main');
        expect(message?.type).assertEqual(A2UIMessageType.UPDATE_DATA_MODEL);
      });

      it('should_parse_update_data_model_with_complex_value', 0, () => {
        let dsl = '{"version":"v0.9","updateDataModel":{"surfaceId":"main","value":{"nested":{"deep":"value"}}}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.type).assertEqual(A2UIMessageType.UPDATE_DATA_MODEL);
      });

      it('should_parse_update_data_model_with_null_value', 0, () => {
        let dsl = '{"version":"v0.9","updateDataModel":{"surfaceId":"main","value":null}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.type).assertEqual(A2UIMessageType.UPDATE_DATA_MODEL);
      });

      it('should_return_null_when_update_data_model_missing_surfaceId', 0, () => {
        let dsl = '{"version":"v0.9","updateDataModel":{"value":{}}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });
    });

    describe('fromDSL_DeleteSurface', () => {
      it('should_parse_delete_surface_message', 0, () => {
        let dsl = '{"version":"v0.9","deleteSurface":{"surfaceId":"main"}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.version).assertEqual('v0.9');
        expect(message?.surfaceId).assertEqual('main');
        expect(message?.type).assertEqual(A2UIMessageType.DELETE_SURFACE);
      });

      it('should_return_null_when_delete_surface_missing_surfaceId', 0, () => {
        let dsl = '{"version":"v0.9","deleteSurface":{}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });
    });

    describe('fromDSL_InvalidInput', () => {
      it('should_return_null_for_invalid_json', 0, () => {
        let dsl = 'not a valid json';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });

      it('should_return_null_for_empty_string', 0, () => {
        let dsl = '';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });

      it('should_return_null_for_whitespace_string', 0, () => {
        let dsl = '   ';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });

      it('should_return_null_when_missing_version', 0, () => {
        let dsl = '{"createSurface":{"surfaceId":"main"}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });

      it('should_return_null_when_version_is_null', 0, () => {
        let dsl = '{"version":null,"createSurface":{"surfaceId":"main"}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });

      it('should_return_null_for_unknown_message_type', 0, () => {
        let dsl = '{"version":"v0.9","unknownType":{"surfaceId":"main"}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });

      it('should_return_null_for_empty_json_object', 0, () => {
        let dsl = '{}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });

      it('should_return_null_when_json_array', 0, () => {
        let dsl = '[]';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });

      it('should_return_null_when_json_is_number', 0, () => {
        let dsl = '123';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });

      it('should_return_null_when_json_is_boolean_true', 0, () => {
        let dsl = 'true';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });

      it('should_return_null_when_json_is_boolean_false', 0, () => {
        let dsl = 'false';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });

      it('should_return_null_when_json_is_null_literal', 0, () => {
        let dsl = 'null';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });

      it('should_return_null_for_unclosed_json_object', 0, () => {
        let dsl = '{"version":"v0.9"';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });

      it('should_return_null_for_json_with_syntax_error', 0, () => {
        let dsl = '{"version":"v0.9",}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message).assertNull();
      });
    });

    describe('fromDSL_SpecialCharacters', () => {
      it('should_handle_special_characters_in_surfaceId', 0, () => {
        let dsl = '{"version":"v0.9","createSurface":{"surfaceId":"test-surface_123"}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.surfaceId).assertEqual('test-surface_123');
      });

      it('should_handle_unicode_in_surfaceId', 0, () => {
        let dsl = '{"version":"v0.9","createSurface":{"surfaceId":"主界面"}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.surfaceId).assertEqual('主界面');
      });

      it('should_handle_escaped_characters_in_json', 0, () => {
        let dsl = '{"version":"v0.9","createSurface":{"surfaceId":"test\\"name"}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.surfaceId).assertEqual('test"name');
      });
    });

    describe('fromDSL_EdgeCases', () => {
      it('should_handle_version_with_numbers', 0, () => {
        let dsl = '{"version":"1.2.3","createSurface":{"surfaceId":"main"}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.version).assertEqual('1.2.3');
      });

      it('should_handle_additional_fields_in_message', 0, () => {
        let dsl = '{"version":"v0.9","extra":"field","createSurface":{"surfaceId":"main","extraField":"value"}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.version).assertEqual('v0.9');
        expect(message?.surfaceId).assertEqual('main');
      });

      it('should_handle_numeric_surfaceId', 0, () => {
        let dsl = '{"version":"v0.9","createSurface":{"surfaceId":123}}';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.surfaceId).assertEqual('123');
      });

      it('should_handle_message_with_whitespace', 0, () => {
        let dsl = '{ "version" : "v0.9" , "createSurface" : { "surfaceId" : "main" } }';
        let message = A2UIMessage.fromDSL(dsl);

        expect(message !== null).assertTrue();
        expect(message?.version).assertEqual('v0.9');
        expect(message?.surfaceId).assertEqual('main');
      });
    });

    describe('A2UIMessageType', () => {
      it('should_have_correct_enum_values', 0, () => {
        expect(A2UIMessageType.CREATE_SURFACE).assertEqual(0);
        expect(A2UIMessageType.UPDATE_COMPONENTS).assertEqual(1);
        expect(A2UIMessageType.UPDATE_DATA_MODEL).assertEqual(2);
        expect(A2UIMessageType.DELETE_SURFACE).assertEqual(3);
      });
    });
  });
}
