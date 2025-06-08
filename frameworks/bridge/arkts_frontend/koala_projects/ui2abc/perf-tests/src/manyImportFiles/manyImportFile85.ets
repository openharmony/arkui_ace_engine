
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent170 } from "./manyImportFile170"
import { ManyImportComponent171 } from "./manyImportFile171"


@Component
export struct ManyImportComponent85 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent170()
            ManyImportComponent171()

        }
    }
}
