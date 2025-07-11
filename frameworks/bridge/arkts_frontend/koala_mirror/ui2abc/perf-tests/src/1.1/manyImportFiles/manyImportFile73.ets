
import { ManyImportComponent146 } from "./manyImportFile146"
import { ManyImportComponent147 } from "./manyImportFile147"


@Component
export struct ManyImportComponent73 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent146()
            ManyImportComponent147()

        }
    }
}
