
import { ManyImportComponent158 } from "./manyImportFile158"
import { ManyImportComponent159 } from "./manyImportFile159"


@Component
export struct ManyImportComponent79 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent158()
            ManyImportComponent159()

        }
    }
}
