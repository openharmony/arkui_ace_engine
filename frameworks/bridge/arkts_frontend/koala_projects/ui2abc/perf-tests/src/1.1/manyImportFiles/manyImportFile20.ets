
import { ManyImportComponent40 } from "./manyImportFile40"
import { ManyImportComponent41 } from "./manyImportFile41"


@Component
export struct ManyImportComponent20 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent40()
            ManyImportComponent41()

        }
    }
}
