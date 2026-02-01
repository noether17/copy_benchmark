import argparse
import json
import matplotlib.pyplot as plt
import numpy as np
import re

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("filename")
    args = parser.parse_args()
    filename = args.filename

    with open(filename) as input_file:
        data = json.load(input_file)
        caches = data["context"]["caches"]
        benchmarks = np.array(data["benchmarks"])

    family_names = np.array([bm["name"].split('/')[0] for bm in benchmarks])
    template_params = parse_template_params(family_names)
    copiers = template_params[0, :]
    data_types = template_params[1, :]
    data_bit_sizes = np.array([int(re.match(r'std::uint(\d+)_t', data_type)[1])
                               for data_type in data_types])
    data_byte_sizes = data_bit_sizes // 8
    n_items = np.array([int(bm["name"].split('/')[1]) for bm in benchmarks])
    bytes_per_second = np.array([bm["bytes_per_second"] for bm in benchmarks])
    items_per_second = np.array([bm["items_per_second"] for bm in benchmarks])

    for data_byte_size in unique_list(data_byte_sizes):
        current_size_indices, = np.where(data_byte_sizes == data_byte_size)
        current_size_bms = benchmarks[current_size_indices]

        plt.figure(figsize=(16, 12))
        for copier in unique_list(copiers[current_size_indices]):
            if "warmup" in copier:
                continue
            elif "memcpy" in copier:
                color = 'b'
            elif "copy_n" in copier:
                color = 'g'
            else:
                color = 'r'
            if "restrict" in copier:
                marker = '+'
            else:
                marker = '.'
            current_copier_indices, = \
                    np.where(copiers[current_size_indices] == copier)
            current_copier_bms = current_size_bms[current_copier_indices]
            current_copier_n_items = \
                    np.array([int(bm["name"].split('/')[1])
                              for bm in current_copier_bms])
            current_copier_bytes = data_byte_size * current_copier_n_items
            current_copier_bytes_per_second = \
                    np.array([float(bm["bytes_per_second"])
                              for bm in current_copier_bms])
            plt.semilogx(current_copier_bytes, current_copier_bytes_per_second,
                         label=copier, color=color, marker=marker)
        out_filename = filename.split('.')[0] + f"_{data_byte_size}_plot.png"
        plt.xlabel("Bytes")
        plt.ylabel("Bytes per Second")
        plt.title(f"Copy performance with {data_byte_size}B elements")
        plt.legend()
        plt.grid()
        plt.savefig(out_filename)

def unique_list(input_list):
    '''Get list of unique values that maintains order of first appearance'''
    result = []
    result_items = set()
    for item in input_list:
        if item not in result_items:
            result_items.add(item)
            result.append(item)
    return result

def parse_template_params(family_names):
    return np.array([family_name[family_name.find('<') + 1:
                                family_name.rfind('>')].split(', ')
                     for family_name in family_names]).transpose()

if __name__ == "__main__":
    main()
