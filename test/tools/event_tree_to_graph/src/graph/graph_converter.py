#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# Copyright (c) 2024 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

from typing import List

# convert the dump result into graphical representation

from graphviz import Digraph

from src.beans.event_node import EventNode
from src.beans.event_procedures import EventProcedures
from src.beans.event_scope import EventScope
from src.beans.event_tree import EventTree

output_folder = 'output'


def reset_output_dir():
    import os
    if os.path.exists(output_folder):
        import shutil
        shutil.rmtree(output_folder)
    os.mkdir(output_folder)


def draw_title_and_touch_points(tree: EventTree, tree_name, dot):
    touch_points = tree.touch_points
    current_index = 0
    touch_points_info = "event tree " + str(tree.tree_id) + '\n'
    for touch_point in touch_points:
        touch_points_info += touch_point.to_summary_string() + '\n'
        current_index += 1
    touch_points_info.rstrip('\n')
    if current_index != 0:
        sub_graph = Digraph(comment='touch points')
        sub_graph.node(tree_name, touch_points_info, shape='box')
        dot.subgraph(sub_graph)


class ParentChildrenPair:
    item_self: EventNode = None  # parent
    children: List['ParentChildrenPair'] = []

    def __init__(self, item):
        self.item_self = item
        self.children = []

    def append_child(self, child):
        self.children.append(child)

    def get_address(self):
        return self.item_self.address


def build_event_node_tree(scope: EventScope):
    result = []
    node_map = {}
    flatten_frame_nodes: List[EventNode] = scope.event_nodes
    # make a mapping table
    for item in flatten_frame_nodes:
        node_map[item.address] = ParentChildrenPair(item)
    # # append child nodes to their parent's `children` attribute based on `parentId`
    for item in flatten_frame_nodes:
        if item.parentId is not None and item.parentId != 0 and len(item.parentId) > 6:
            node_map[item.parentId].append_child(node_map[item.address])
        else:
            result.append(node_map[item.address])
    return result


# draw node relationships recursively
def draw_event_scop_tree_recursively(node_tree: List[ParentChildrenPair], parent_node_name: str, graph: Digraph,
                                     is_show_detail):
    for item in node_tree:
        node_name = item.get_address()
        node_label = item.item_self.get_summary_string()
        if is_show_detail:
            node_label = item.item_self.get_detailed_summary_string()
        graph.node(node_name, node_label)
        if parent_node_name is not None:
            graph.edge(parent_node_name, node_name)
        if len(item.children) > 0:
            draw_event_scop_tree_recursively(item.children, node_name, graph, is_show_detail)


def draw_event_procedures(tree: EventTree, tree_name, dot, is_show_detail):
    event_procedures: EventProcedures = tree.event_procedures
    if event_procedures is None:
        return
    tag = str(tree.tree_id) + ' event procedures'
    sub_graph = Digraph(comment=tag)
    for scope in event_procedures.event_scopes:
        sub_scope_graph = Digraph(comment=tag + ' event scope ' + str(scope.finger))
        node_tree = build_event_node_tree(scope)
        # treat finger as root node of subgraph
        scope_root_node_name = 'finger ' + str(scope.finger)
        sub_scope_graph.node(scope_root_node_name, scope_root_node_name)
        dot.edge(tree_name, scope_root_node_name)
        draw_event_scop_tree_recursively(node_tree, scope_root_node_name, sub_scope_graph, is_show_detail)
        sub_graph.subgraph(sub_scope_graph)
    dot.subgraph(sub_graph)


def generate_event_trees_graph(dump_result, is_show_detail):
    # delete all history files before generate new ones
    reset_output_dir()
    current_index = 0
    # draw every event tree into file
    for tree in dump_result.event_trees:
        # create a graph
        dot = Digraph(comment='event dump' + str(current_index))
        # draw touch points info
        tree_name = 'event tree ' + str(tree.tree_id)
        draw_title_and_touch_points(tree, tree_name, dot)
        # draw event procedures
        draw_event_procedures(tree, tree_name, dot, is_show_detail)
        # save or show directly
        # dot.view()
        # or save to file
        out_graph_file_name = output_folder + '/view_tree_' + str(tree.tree_id)
        dot.render(out_graph_file_name, format='svg', cleanup=True, view=False)
        current_index += 1
