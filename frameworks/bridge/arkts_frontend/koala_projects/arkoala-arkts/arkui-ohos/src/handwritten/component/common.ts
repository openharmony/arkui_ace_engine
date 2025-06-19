
export function applyStyles<T extends CommonMethod>(this: T, customStyles: CustomStyles): T {
    customStyles(this);
    return this;
}