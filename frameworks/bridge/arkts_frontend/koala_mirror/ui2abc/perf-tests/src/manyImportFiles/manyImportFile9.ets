
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent18 } from "./manyImportFile18"
import { ManyImportComponent19 } from "./manyImportFile19"


@Component
export struct ManyImportComponent9 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent18()
            ManyImportComponent19()

        }
    }
}
