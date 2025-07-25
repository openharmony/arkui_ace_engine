@Entry
@Component
struct FormLinkTest {
    options1: FormLinkOptions = { action: "router", moduleName: "Module", bundleName: "Bundle",
        abilityName: "MainAbility", uri: "Uri", params: { method: "Fun1", num: 1 } }

    build() {
        FormLink(this.options1)
    }
}
