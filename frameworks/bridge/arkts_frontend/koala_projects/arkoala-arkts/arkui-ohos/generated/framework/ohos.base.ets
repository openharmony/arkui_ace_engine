import { SerializerBase, DeserializerBase } from "@koalaui/interop"

// instructive changes, need to be removed
import { BusinessError } from "@ohos.base"
// instructive changes, need to be removed

export type Callback<T> = (data: T) => void;
export type ErrorCallback<T = undefined> = (err: T)=> void;
export type AsyncCallback<T> = (err: BusinessError | null, data: T | undefined) => void;

export class BusinessError_serializer {
    public static write<T = void>(buffer: SerializerBase, value: BusinessError<T>): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(123)
    }
    public static read<T = void>(buffer: DeserializerBase): BusinessError<T> {
        let valueDeserializer : DeserializerBase = buffer
        let ptr = valueDeserializer.readPointer()
        // instructive change begin
        return { code: 0, message: '', name: '' } as BusinessError<T>
        // instructive change end
    }
}
