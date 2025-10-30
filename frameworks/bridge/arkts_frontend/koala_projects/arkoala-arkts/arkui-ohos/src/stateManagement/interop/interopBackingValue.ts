import { staticStateBindObservedObject } from '../../component/interop';
import { DecoratorBackingValue } from '../base/backingValue';
import { ObserveSingleton } from '../base/observeSingleton';
import { IMutableStateMeta, STATE_MGMT_FACTORY } from '../decorator';

export class InteropDecoratorBackingValue<T> extends DecoratorBackingValue<T> {
    trackProperties: Map<string, IMutableStateMeta> = new Map<string, IMutableStateMeta>();

    constructor(propertyName: string, initValue: T) {
        super(propertyName, initValue)
        staticStateBindObservedObject(
            initValue,
            () => this.fireChange(),
            this.onTrackPropertyRead,
            this.onTrackPropertyChange
        )
    }

    public onTrackPropertyRead(property: string, isTracked: boolean): void {
        let record = this.trackProperties.get(property);
        if (!record) {
            record = STATE_MGMT_FACTORY.makeMutableStateMeta() as IMutableStateMeta;
            this.trackProperties.set(property, record);    
        }
        record!.addRef();
    }

    public onTrackPropertyChange(property: string): void {
        let record = this.trackProperties.get(property);
        if (record) {
            record.fireChange();
        }
    }

    public setNoCheck(newValue: T): void {
        super.setNoCheck(newValue);
        staticStateBindObservedObject(
            newValue,
            () => this.fireChange(),
            this.onTrackPropertyRead,
            this.onTrackPropertyChange
        )
    }
}