#!/usr/bin/env python
# -*- coding: utf-8 -*-

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

import os
import struct
import sys


def int_to_str(int_n):
    buf = ""
    i = 0
    while i < 4:
        a = ((int_n >> (3 - i) * 8) & 0xff)
        if a != 0:
            buf = buf + chr(a)
        i = i + 1
    return buf


resolutions = {-2: "nodpi", -1: "anydpi", 120: "sdpi", 160: "mdpi", 213: "tvdpi", 240: "ldpi", 320: "xldpi",
               480: "xxldpi", 640: "xxxldpi"}

orientations = {0: "vertical", 1: "horizontal"}

devices = {0: "phone", 1: "tablet", 2: "car", 3: "pc", 4: "tv", 5: "speaker", 6: "wearable", 7: "glasses", 8: "headset"}

night_modes = {0: "dark", 1: "light"}


def parse_limit_key(limit_key):
    key_str = ""
    key_ = limit_key
    if key_ == "":
        key_ = "base"
        key_str = "base"

    key_sets = key_.split("-")
    last_key_type = -1
    for key_item in key_sets:
        if key_item == "base":
            continue
        key_s = key_item.split(":")
        if int(key_s[0]) == 0 or int(key_s[0]) == 1 or int(key_s[0]) == 5:
            i = int(key_s[1])
            if key_str == "":
                key_str = key_str + int_to_str(i)
            elif last_key_type == 0 or last_key_type == 1 or last_key_type == 5:
                key_str = "{}_{}".format(key_str, int_to_str(i))
            else:
                key_str = "{}-{}".format(key_str, int_to_str(i))
            last_key_type = int(key_s[0])
        elif int(key_s[0]) == 2:
            k = int(key_s[1])
            if (k & 0x80000000) != 0:
                a = (0xffffffff ^ k) + 1
                k = -1 * a
            if key_str == "":
                key_str = key_str + resolutions.get(k)
            else:
                key_str = "{}-{}".format(key_str, resolutions.get(k))
        elif int(key_s[0]) == 3:
            if key_str == "":
                key_str = key_str + orientations.get(int(key_s[1]))
            else:
                key_str = "{}-{}".format(key_str, orientations.get(int(key_s[1])))
        elif int(key_s[0]) == 4:
            if key_str == "":
                key_str = key_str + devices.get(int(key_s[1]))
            else:
                key_str = "{}-{}".format(key_str, devices.get(int(key_s[1])))
        elif int(key_s[0]) == 6:
            if key_str == "":
                key_str = key_str + night_modes.get(int(key_s[1]))
            else:
                key_str = "{}-{}".format(key_str, night_modes.get(int(key_s[1])))
        elif int(key_s[0]) == 7:
            i = int(key_s[1])
            if key_str == "":
                key_str = "{}mcc{}".format(key_str, str(i))
            else:
                key_str = "{}_mcc{}".format(key_str, str(i))
        elif int(key_s[0]) == 8:
            i = int(key_s[1])
            if key_str == "":
                key_str = "{}mnc{:0>2d}".format(key_str, i)
            else:
                key_str = "{}_mnc{:0>2d}".format(key_str, i)
        else:
            raise Exception("invalid key={}".format(str(int(key_s[0]))))
    return key_str


def open_new_resource_index(file_path):
    if not os.path.exists(file_path):
        raise Exception("not found:" + file_path)

    with open(file_path, "rb") as fp_resource_index:
        header = fp_resource_index.read(128)
        length = fp_resource_index.read(4)
        key_count = fp_resource_index.read(4)
        pri_key_count = struct.unpack("i", key_count)[0]

        index_one = 0

        # keys
        private_index = {}
        while index_one < pri_key_count:
            buf = fp_resource_index.read(4)
            p_key_tag = struct.unpack("4s", buf)[0]

            buf = fp_resource_index.read(4)
            p_data_offset = struct.unpack("I", buf)[0]

            buf = fp_resource_index.read(4)
            p_key_count = struct.unpack("I", buf)[0]

            i = 0
            key_str = ""
            while i < p_key_count:
                buf = fp_resource_index.read(8)
                p_key_type = struct.unpack("I", buf[0:4])[0]
                p_value = struct.unpack("I", buf[4:8])[0]
                if key_str == "":
                    key_str = "{}:{}".format(str(p_key_type), str(p_value))
                else:
                    key_str = "{}-{}:{}".format(key_str, str(p_key_type), str(p_value))
                i = i + 1
            private_index[key_str] = p_data_offset
            index_one = index_one + 1

        # idss
        c = 0
        idss_cache = {}
        while c < pri_key_count:
            pos = fp_resource_index.tell()
            idss_buf = fp_resource_index.read(4)
            idss_tag = struct.unpack("4s", idss_buf)[0]
            idss_buf = fp_resource_index.read(4)
            idss_count = struct.unpack("I", idss_buf)[0]
            i = 0
            idss_index = {}
            while i < idss_count:
                buf = fp_resource_index.read(4)
                p_id = struct.unpack("I", buf)[0]
                buf = fp_resource_index.read(4)
                p_offset = struct.unpack("I", buf)[0]
                idss_index[p_id] = p_offset
                i = i + 1
            idss_cache[pos] = idss_index
            c = c + 1

        third_data = {}
        d_data = {}
        d_pos = fp_resource_index.tell()
        d_buf = fp_resource_index.read(4)
        while len(d_buf) > 0:
            d_size = struct.unpack("I", d_buf)[0]
            d_buf = fp_resource_index.read(d_size)
            d_res_type = struct.unpack("I", d_buf[0:4])[0]

            d_value_len_l = struct.unpack("B", d_buf[8:9])[0]
            d_value_len_h = struct.unpack("B", d_buf[9:10])[0]
            d_value_len = d_value_len_l + d_value_len_h * 256
            d_value = ""
            if d_res_type == 10 or d_res_type == 11 or d_res_type == 16 or d_res_type == 17 or d_res_type == 22:
                tmp = d_buf[10:10 + d_value_len]
                d_d_pos = 0
                while d_d_pos < d_value_len - 1:
                    d_d_value_len_l = struct.unpack("B", tmp[0 + d_d_pos:1 + d_d_pos])[0]
                    d_d_value_len_h = struct.unpack("B", tmp[1 + d_d_pos:2 + d_d_pos])[0]
                    d_d_value_len = d_d_value_len_l + d_d_value_len_h * 256
                    d_value = "{}<{}>".format(d_value, str(tmp[2 + d_d_pos:2 + d_d_value_len + d_d_pos]))
                    d_d_pos = d_d_pos + 2 + d_d_value_len + 1
            else:
                d_value = d_buf[10:10 + d_value_len - 1].decode("utf-8")

            d_name_len_l = struct.unpack("B", d_buf[10 + d_value_len:11 + d_value_len])[0]
            d_name_len_h = struct.unpack("B", d_buf[11 + d_value_len:12 + d_value_len])[0]
            d_name_len = d_name_len_l + d_name_len_h * 256
            d_name = str(d_buf[12 + d_value_len:12 + d_value_len + d_name_len - 1].decode("utf-8"))
            d_data[d_pos] = [d_value, d_name]

            d_pos = fp_resource_index.tell()
            d_buf = fp_resource_index.read(4)

    for key_, key_offset in private_index.items():
        third_data[key_] = {}
        idss_sets = idss_cache.get(key_offset)
        for id_, offset in idss_sets.items():
            id_sets = d_data.get(offset)
            third_data[key_][id_] = id_sets
    return third_data


def dump(file_path, out_path):
    out_file = os.open(out_path, os.O_WRONLY | os.O_CREAT, 0o664)
    third_data = open_new_resource_index(file_path)
    for key_, ids_ in third_data.items():
        key_str = parse_limit_key(key_)
        if "zh_CN" == key_str:
            continue
        os.write(out_file, str.encode("keyconfig:{}\n".format(key_)))
        os.write(out_file, str.encode("{}\n".format(key_str)))
        for id_, idsets in ids_.items():
            os.write(out_file, str.encode("id:{}, '{}' '{}'\n".format(str(id_), idsets[0], str(idsets[1]))))
    os.close(out_file)
