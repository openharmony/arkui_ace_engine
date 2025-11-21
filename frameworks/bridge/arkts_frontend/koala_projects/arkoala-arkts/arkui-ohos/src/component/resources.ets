import { Resource } from "global.resource";
import { int32 } from "@koalaui/common";
import { ArkUIGeneratedNativeModule } from "#components";
import { InteropNativeModule } from "@koalaui/interop";
import { SystemOps } from "#generated";

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
    RAWFILE = 30000,
    SYMBOL = 40000
}

const re = new RegExp("^\\[\\S+?]");

export class ArkResource implements Resource {
    bundleName: string = "";
    moduleName: string = "";
    params?: Array<string | int | long | double | Resource> | undefined;
    type?: int32 | undefined;
    _id: long = -1;

    castParams(params: Array<string | int | long | double | Resource>): Array<string | int | long | double | Resource> {
        let result: Array<string | int | long | double | Resource> = new Array<string | int | long | double | Resource>();
        for (let param of params) {
            result.push(param);
        }
        return result;
    }

    constructor(resourceName: string | null, bundleName: string, moduleName: string, ...params: Array<string | int | long | double | Resource>) {
        this.bundleName = bundleName;
        this.moduleName = moduleName;
        if (resourceName !== null) {
            let param1 = new Array<string | int | long | double | Resource>();
            param1.push(resourceName);
            this.params = param1.concat(this.castParams(params));
        } else {
            this.params = this.castParams(params);
        }
        this._id = -1;
        if (this.params!.length > 0) {
            const name: string = this.params![0] as string;
            this.type = this.parseResourceType(name);
        } else {
            InteropNativeModule._NativeLog("UI-Plugin do not send resourceName when id is -1");
        }
    }
    constructor(id: long, type: int32, bundleName: string, moduleName: string, ...params: Array<string | int | long | double | Resource>) {
        this._id = id;
        this.type = type;
        this.params = this.castParams(params);
        this.bundleName = bundleName;
        this.moduleName = moduleName;
    }
    constructor(id: long, type: int32 | undefined, bundleName: string, moduleName: string) {
        this._id = id;
        this.type = type;
        this.bundleName = bundleName;
        this.moduleName = moduleName;
    }
    set id(value: long) {
        this._id = value;
    }
    get id(): long {
        if (this._id == -1) {
            this._id = SystemOps.getResourceId(this.bundleName, this.moduleName, [
                (this.params![0] as string).replace(re, 'app'),
            ]);
            if (this.id > -1 && this.params!.length > 0) {
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
            case 'symbol':
                return ResourceType.SYMBOL;
        }
        return ResourceType.STRING;
    }
}
export function _r(bundleName: string, moduleName: string, name: string, ...params: Array<string | int | long | double | Resource>): Resource {
    return new ArkResource(name, bundleName, moduleName, ...params)
}
export function _rawfile(bundleName: string, moduleName: string, name: string): Resource {
    return new ArkResource(0, 30000, bundleName, moduleName, name);
}
export function _r(id: number, type: number, bundleName: string, moduleName: string, ...params: Array<string | int | long | double | Resource>): Resource {
    if (id === -1) {
        return new ArkResource(null, bundleName, moduleName, ...params);
    }
    return new ArkResource(id as long, type as int32, bundleName, moduleName, ...params);
}
export function _rawfile(id: number, type: number, bundleName: string, moduleName: string, ...params: Array<string | int | long | double | Resource>): Resource {
    const name: string = params[0] as string;
    return _rawfile(bundleName, moduleName, name);
}
