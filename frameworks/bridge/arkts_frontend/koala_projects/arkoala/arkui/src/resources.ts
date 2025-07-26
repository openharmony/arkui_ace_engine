export function _r(bundleName: string, moduleName: string, name: string): Resource {
    const param: string = name.split(".")[1];
    let res_type = 20000;

    switch (param) {
        case 'media':
            res_type = 20000;
            break;
        case 'color':
            res_type = 10001;
            break;
        case 'string':
            res_type = 10003;
            break;
        case 'float':
            res_type = 10002;
            break;
    }


    return {
        "id": -1,
        "type": res_type,
        "params": new Array<string>(name),
        "bundleName": bundleName,
        "moduleName": moduleName
    } as Resource
}

export function _rawfile(bundleName: string, moduleName: string, name: string): Resource {
    return {
        "id": 0,
        "type": 30000,
        "params": new Array<string>(name),
        "bundleName": bundleName,
        "moduleName": moduleName
    } as Resource
}

export function __registerResources(bundleName: string, moduleName: string, resources: Record<string, number>) {}