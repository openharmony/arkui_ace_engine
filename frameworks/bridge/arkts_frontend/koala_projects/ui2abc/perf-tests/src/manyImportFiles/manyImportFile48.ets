
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent96 } from "./manyImportFile96"
import { ManyImportComponent97 } from "./manyImportFile97"


@Component
export struct ManyImportComponent48 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent96()
            ManyImportComponent97()

        }
    }
}
