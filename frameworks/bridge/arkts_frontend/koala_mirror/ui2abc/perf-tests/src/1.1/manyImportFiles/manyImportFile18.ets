
import { ManyImportComponent36 } from "./manyImportFile36"
import { ManyImportComponent37 } from "./manyImportFile37"


@Component
export struct ManyImportComponent18 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent36()
            ManyImportComponent37()

        }
    }
}
