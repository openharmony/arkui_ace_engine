/**
 * `CustomComponent` is not annotated with `memo` whereas its real semantic assumes some of its methods
 * are actually `memo` methods. Calling those methods on `CustomComponent` type leads to loosing `memo`
 * context. To avoid that the annotated `ArkCustomComponent` subclass should be used instead.
 */
export abstract class ArkCustomComponent extends CustomComponent {
    
    setInstanceId(value: number): void {}
    /** @memo */
    abstract build(): void;
    /** @memo */
    abstract pageTransition?(): void;
}
