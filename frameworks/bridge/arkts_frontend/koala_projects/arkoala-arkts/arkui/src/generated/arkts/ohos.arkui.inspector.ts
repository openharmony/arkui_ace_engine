import { loadNativeModuleLibrary } from "@koalaui/interop"

export class ComponentObserver {
    private nativeComponentObserver: long = 0;
        
    constructor(nativeAddr: long) {
        if (this.nativeComponentObserver == 0) {
            this.nativeComponentObserver = nativeAddr;
        }
    }
    
    public native on(type: string, callback: ()=>void) : void;

    public native off(type: string, callback?: ()=>void) : void;
}

export class Inspector {
    static {
        loadNativeModuleLibrary("inspector_ani");
    }
    native static createComponentObserver(id: string): ComponentObserver;
}