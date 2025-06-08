
import { ManyImportComponent130 } from "./manyImportFile130"
import { ManyImportComponent131 } from "./manyImportFile131"


@Component
export struct ManyImportComponent65 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent130()
            ManyImportComponent131()

        }
    }
}
