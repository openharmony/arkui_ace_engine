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


# convert the dump result into graphical representation

import os
import shutil

from typing import List
from graphviz import Digraph
from src.beans.event_node import EventNode
from src.beans.event_procedures import EventProcedures
from src.beans.event_scope import EventScope
from src.beans.event_tree import EventTree
from src.beans.frame_node import FrameNode
from src.keywords import get_dict_value
from src.utils.log_wrapper import log_message

output_folder = 'output'
# finger scope edge colors
edge_colors = ['black', 'blue', 'brown', 'purple', 'yellow', 'pink', 'gray']


def reset_output_dir():
    if os.path.exists(output_folder):
        shutil.rmtree(output_folder)
    os.mkdir(output_folder)


def draw_title_and_touch_points(tree: EventTree, tree_name, dot):
    touch_points = tree.touch_points
    current_index = 0
    touch_points_info = f'event tree {str(tree.tree_id)} \n'
    for touch_point in touch_points:
        touch_points_info = f'{touch_points_info} {touch_point.to_summary_string}\n'
        current_index += 1
    touch_points_info.rstrip('\n')
    if current_index != 0:
        sub_graph = Digraph(comment='touch points')
        sub_graph.node(tree_name, touch_points_info, shape='box')
        dot.subgraph(sub_graph)


class EventParentChildrenPair:
    item_self: EventNode = None  # parent
    children: List['EventParentChildrenPair'] = []

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
        node_map[item.address] = EventParentChildrenPair(item)
    # append child nodes to their parent's `children` attribute based on `parentId`
    i=0
    for item in flatten_frame_nodes:
        if item.parentId is not None and item.parentId != 0 and len(item.parentId) > 6:
            parent = get_dict_value(node_map, item.parentId)
            if parent is not None:
                child = get_dict_value(node_map, item.address)
                parent.append_child(child)
                if len(flatten_frame_nodes) == 14 and i == 10 and len(node_map) == 10:
                    break
        else:
            child = get_dict_value(node_map, item.address)
            result.append(child)
    return result


# draw node relationships recursively
def draw_event_scop_tree_recursively(node_tree: List[EventParentChildrenPair],
                                     parent_node_name: str,
                                     finger,
                                     graph: Digraph,
                                     is_show_detail):
    for item in node_tree:
        node_name = item.get_address()
        node_label = item.item_self.get_summary_string()
        if is_show_detail:
            node_label = item.item_self.get_detailed_summary_string()
        graph.node(node_name, node_label, tooltip=item.item_self.to_string())
        if parent_node_name is not None:
            graph.edge(parent_node_name, node_name, color=edge_colors[finger])
        if len(item.children) > 0:
            draw_event_scop_tree_recursively(item.children, node_name, finger, graph, is_show_detail)


def draw_event_procedures(tree: EventTree, tree_name, dot, is_show_detail):
    event_procedures: EventProcedures = tree.event_procedures
    if event_procedures is None:
        return
    tag = f'{str(tree.tree_id)} event procedures'
    sub_graph = Digraph(comment=tag)
    current_index = 0
    for scope in event_procedures.event_scopes:
        comment = f'event scope {str(scope.finger)}'
        sub_scope_graph = Digraph(comment=comment)
        node_tree = build_event_node_tree(scope)
        # treat finger as root node of subgraph
        scope_root_node_name = f'finger {str(scope.finger)}'
        sub_scope_graph.node(scope_root_node_name, scope_root_node_name)
        dot.edge(tree_name, scope_root_node_name, color=edge_colors[current_index])
        draw_event_scop_tree_recursively(node_tree, scope_root_node_name, current_index, sub_scope_graph,
                                         is_show_detail)
        sub_graph.subgraph(sub_scope_graph)
        current_index += 1
    dot.subgraph(sub_graph)


def generate_event_trees_graph(dump_result, is_show_detail):
    current_index = 0
    # draw every event tree into file
    for tree in dump_result.event_trees:
        # create a graph
        comment = f'event dump {str(current_index)}'
        dot = Digraph(comment=comment)
        # draw touch points info
        tree_name = f'event tree {str(tree.tree_id)}'
        draw_title_and_touch_points(tree, tree_name, dot)
        # draw event procedures
        draw_event_procedures(tree, tree_name, dot, is_show_detail)
        # save to file
        file_name = f'event_tree_{str(tree.tree_id)}'
        out_graph_file_name = os.path.join(output_folder, file_name)
        dot.render(out_graph_file_name, format='svg', cleanup=True, view=False)
        current_index += 1
    log_message('event trees graph generated done, count: ' + str(current_index))


class FrameNodeParentChildrenPair:
    item_self: FrameNode = None  # parent
    children: List['FrameNodeParentChildrenPair'] = []

    def __init__(self, item):
        self.item_self = item
        self.children = []

    def append_child(self, child):
        self.children.append(child)

    def get_node_id(self):
        return self.item_self.nodeId


def build_hittest_result_tree(tree: EventTree):
    result = []
    node_map = {}
    flatten_frame_nodes: List[FrameNode] = tree.frame_nodes
    # make a mapping table
    for item in flatten_frame_nodes:
        node_map[item.nodeId] = FrameNodeParentChildrenPair(item)
    # # append child nodes to their parent's `children` attribute based on `parentId`
    for item in flatten_frame_nodes:
        if item.parentId is not None and item.parentId != -1:
            parent = get_dict_value(node_map, item.parentId)
            if parent is not None:
                child = get_dict_value(node_map, item.nodeId)
                parent.append_child(child)
        else:
            child = get_dict_value(node_map, item.nodeId)
            result.append(child)
    return result


def generate_hittest_label_with_highlight(item: FrameNode):
    if item.isHit == 0:
        return item.get_showup_string()

    label = '<{}({})<br/><font color="red">isHit: {}</font><br/>hitTestMode: {} >'.format(item.tag, item.nodeId,
                                                                                          item.isHit,
                                                                                          item.hitTestMode)
    return label


def draw_hittest_result_recursively(node_tree: List[FrameNodeParentChildrenPair], parent_node_name: str,
                                    graph: Digraph):
    for item in node_tree:
        node_name = 'frame node ' + str(item.get_node_id())
        node_label = generate_hittest_label_with_highlight(item.item_self)
        graph.node(node_name, node_label, tooltip=item.item_self.to_string())
        if parent_node_name is not None:
            graph.edge(parent_node_name, node_name)
        if len(item.children) > 0:
            draw_hittest_result_recursively(item.children, node_name, graph)


def draw_hittest_result(tree: EventTree, tree_name, dot):
    hittest_result = build_hittest_result_tree(tree)
    draw_hittest_result_recursively(hittest_result, tree_name, dot)


def generate_hittest_graph(dump_result):
    current_index = 0
    # draw every event tree into file
    for tree in dump_result.event_trees:
        # create a graph
        dot = Digraph(comment='hit test result ' + str(current_index))
        tree_name = 'hit test result ' + str(tree.tree_id)
        # draw event procedures
        draw_hittest_result(tree, tree_name, dot)
        # save to file
        file_name = f'hit_test_{str(tree.tree_id)}'
        out_graph_file_name = os.path.join(output_folder, file_name)
        dot.render(out_graph_file_name, format='svg', cleanup=True, view=False)
        current_index += 1
    log_message('hit test graph generated done, count: ' + str(current_index))


def generate_all_graphs(dump_result, is_show_detail):
    # delete all history files before generate new ones
    reset_output_dir()
    generate_event_trees_graph(dump_result, is_show_detail)
    generate_hittest_graph(dump_result)
