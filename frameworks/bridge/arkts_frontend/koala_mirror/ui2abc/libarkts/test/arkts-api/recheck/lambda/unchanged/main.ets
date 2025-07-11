
class HasInstantiate {
    static $_instantiate(factory: () => HasInstantiate, arg: string) {
    }
}

function foo(): void {
    HasInstantiate("foo")
}

function hasTrailing(first?: string, trailing?: () => void): void {
    trailing?.()
}

function bar(zzz: string): void {

    hasTrailing("xxx")

    hasTrailing("xxx") {
        const d = zzz
    }
}

