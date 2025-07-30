import { GeneratedPartialPropertiesType, PeerNode, PeerNodeType } from "@koalaui/arkoala"
import { PeerEventsProperties } from "./peer_events"
import { DataNode, contextNode } from "@koalaui/runtime"

/** @memo */
export function UseEventsProperties(properties: Partial<PeerEventsProperties>) {
    const parent = contextNode<PeerNode>(PeerNodeType)
    DataNode.attach(GeneratedPartialPropertiesType, properties, () => {
        parent.invalidateProperties()
    })
}