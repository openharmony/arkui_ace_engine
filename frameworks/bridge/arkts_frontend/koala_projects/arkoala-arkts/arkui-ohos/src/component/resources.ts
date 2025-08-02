import { Resource } from "global/resource";
import { int32 } from "@koalaui/common";
import { ArkUIGeneratedNativeModule } from "#components";
import { Serializer } from "./peers/Serializer";
import { asArray } from "@koalaui/common";
import { RuntimeType, runtimeType } from "@koalaui/interop";

enum ResourceType {
    COLOR = 10001,
    FLOAT,
    STRING,
    PLURAL,
    BOOLEAN,
    INTARRAY,
    INTEGER,
    PATTERN,
    STRARRAY,
    MEDIA = 20000,
    RAWFILE = 30000
}

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
        this.type = this.parseResourceType(resourceName);
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
                thisSerializer.writeString(String(param[i]));
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
    parseResourceType(resourceName: string): ResourceType {
        const typeName: string = resourceName.split(".")[1];
        switch (typeName) {
            case 'color':
                return ResourceType.COLOR;
            case 'float':
                return ResourceType.FLOAT;
            case 'string':
                return ResourceType.STRING;
            case 'plural':
                return ResourceType.PLURAL;
            case 'boolean':
                return ResourceType.BOOLEAN;
            case 'intarray':
                return ResourceType.INTARRAY
            case 'integer':
                return ResourceType.INTEGER;
            case 'pattern':
                return ResourceType.PATTERN;
            case 'strarray':
                return ResourceType.STRARRAY
            case 'media':
                return ResourceType.MEDIA;
            case 'RAWFILE':
                return ResourceType.RAWFILE;
        }
        return ResourceType.STRING;
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