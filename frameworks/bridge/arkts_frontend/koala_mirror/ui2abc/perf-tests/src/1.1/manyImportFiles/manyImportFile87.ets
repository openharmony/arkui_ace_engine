
import { ManyImportComponent174 } from "./manyImportFile174"
import { ManyImportComponent175 } from "./manyImportFile175"


@Component
export struct ManyImportComponent87 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent174()
            ManyImportComponent175()

        }
    }
}
