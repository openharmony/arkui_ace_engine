
import { ManyImportComponent142 } from "./manyImportFile142"
import { ManyImportComponent143 } from "./manyImportFile143"


@Component
export struct ManyImportComponent71 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent142()
            ManyImportComponent143()

        }
    }
}
