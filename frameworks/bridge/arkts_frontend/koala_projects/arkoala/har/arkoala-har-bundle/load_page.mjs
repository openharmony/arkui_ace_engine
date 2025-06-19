let loader = () => { throw new Error("Page laoder was not set") }

export function __setPageLoader(fn) {
    loader = fn;
}

export default function loadPage(url) {
    return loader(url)
}