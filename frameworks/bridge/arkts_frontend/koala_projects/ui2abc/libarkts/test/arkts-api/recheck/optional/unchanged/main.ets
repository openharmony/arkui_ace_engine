
class X {
    y?: string
}

function foo(x: X|undefined) {
    let zzz = x?.y?.length
}

