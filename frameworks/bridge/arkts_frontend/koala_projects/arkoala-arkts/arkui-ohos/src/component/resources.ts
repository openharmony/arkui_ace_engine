import { Resource } from "global/resource";
import { int32 } from "@koalaui/common";
import { ArkUIGeneratedNativeModule } from "#components";
import { Serializer } from "../generated/peers/Serializer";
import { asArray } from "@koalaui/common";
import { RuntimeType, runtimeType } from "@koalaui/interop";

class ArkResource implements Resource {
    bundleName: string = "";
    moduleName: string = "";
    params?: Array<Object> | undefined;
    type?: number | undefined;
    _id: number = -1;
    constructor(resourceName: string, bundleName: string, moduleName: string, ...params: Object[]) {
        this.bundleName = bundleName;
        this.moduleName = moduleName;
        let param1 = new Array<Object>();
        if (resourceName != null) {
            param1.push(resourceName);
            param1 = param1.concat(asArray(params));
        }
        this.params = param1;
        this._id = -1;
        const param: string = resourceName.split(".")[1];
        this.type = 20000;
        switch (param) {
            case 'media':
                this.type = 20000;
                break;
            case 'color':
                this.type = 10001;
                break;
            case 'string':
                this.type = 10003;
                break;
            case 'float':
                this.type = 10002;
                break;
        }
    }
    set id(value: number) {
        this._id = value;
    }
    get id(): number {
        if (this._id == -1) {
            if (this.params == null || this.params == undefined) {
                return this._id;
            }
            let param = this.params;
            let bundleNamea = this.bundleName;
            let moduleNamea = this.moduleName;
            const thisSerializer: Serializer = Serializer.hold();
            if (param == null) {
                thisSerializer.release();
                return this._id;
            }
            thisSerializer.writeInt32(param.length as int32);
            for (let i = 0; i < param.length; i++) {
                const params_type = runtimeType(param[i]);
                if (params_type == RuntimeType.STRING) {
                    const params_element: string = param[i] as string;
                    thisSerializer.writeString(params_element);
                } else if (params_type == RuntimeType.NUMBER) {
                    const params_element: number = param[i] as number;
                    thisSerializer.writeString(String(params_element));
                } else {
                    throw new Error("Unsupported params type, expect string or number.")
                }
            }
            const retval = ArkUIGeneratedNativeModule._SystemOps_getResourceId(bundleNamea, moduleNamea, thisSerializer.asBuffer(), thisSerializer.length());
            thisSerializer.release();
            this._id = retval;
            if (this.params!.length > 0) {
                this.params!.shift();
            }
        }
        return this._id;
    }
}
export function _r(bundleName: string, moduleName: string, name: string, ...params: Object[]): Resource {
    return new ArkResource(name, bundleName, moduleName, ...params)
}
export function _rawfile(bundleName: string, moduleName: string, name: string): Resource {
    return {
        "id": 0,
        "type": 30000,
        "params": new Array<Object>(name),
        "bundleName": bundleName,
        "moduleName": moduleName
    } as Resource
}