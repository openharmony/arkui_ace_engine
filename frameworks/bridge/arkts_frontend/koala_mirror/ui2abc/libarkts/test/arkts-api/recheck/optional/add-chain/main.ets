class SomeClass {
    y: string = "yyy"
}

function someFunc(value: SomeClass|undefined) {
    let x: SomeClass|undefined = value
    let zzz = x?.y
}

