
import { ManyImportComponent70 } from "./manyImportFile70"
import { ManyImportComponent71 } from "./manyImportFile71"


@Component
export struct ManyImportComponent35 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent70()
            ManyImportComponent71()

        }
    }
}
