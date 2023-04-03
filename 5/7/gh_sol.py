"""
python은 orderedDict을 잘 써 보자.
java만큼은 아니겠지만, 생각보다 lru에 필요한 기능들을 쉽게 가져다 쓸 수 있다.
"""

from collections import OrderedDict
import sys
input = sys.stdin.readline
print = sys.stdout.write


class LRU:
    def __init__(self, cache_size):
        self.cache = OrderedDict()
        self.cache_size = cache_size
    
    def access_station_data(self, key):
        if key in self.cache:
            self.cache.move_to_end(key)
            return True
        else:
            if len(self.cache) >= self.cache_size:
                self.cache.popitem(last=False)
            self.cache[key] = ""
            return False


class Compress:
    def __init__(self, node_data):
        self.bucket_num = -1
        self.node_type = list()
        self.compressed = dict()
        for node_num, node_type in node_data:
            compressed = len(self.compressed)
            self.compressed[node_num] = tuple([compressed, node_type])
            if node_type == 'B':
                self.bucket_num = compressed
            self.node_type.append(node_type)
    
    def get_node_info(self, node_num):
        return self.compressed.get(node_num)
    
    def get_node_type_with_compressed(self, compressed_node_num):
        return self.node_type[compressed_node_num]
    
    def get_bucket_node(self):
        return self.bucket_num


dist = [[0x3f3f3f3f for _ in range(300)] for _ in range(0, 300)]
dp = dict()
node_data = list()
n, m, c_sz, q = map(int, input().split())
for _ in range(n):
    input()
for _ in range(m):
    node_n, node_t = input().split()
    node_n = int(node_n)
    node_data.append(tuple([node_n, node_t]))

node_data = sorted(node_data)
compressed_node_data = Compress(node_data)

road = int(input())
for _ in range(road):
    ff, tt, c = map(int, input().split())
    ff, _ = compressed_node_data.get_node_info(ff)
    tt, _ = compressed_node_data.get_node_info(tt)
    dist[ff][tt] = dist[tt][ff] = min(dist[ff][tt], c)

for k in range(0, 300):
    for i in range(0, 300):
        for j in range(0, 300):
            if dist[i][k] + dist[k][j] < dist[i][j]:
                dist[i][j] = dist[i][k] + dist[k][j]

node_list = list()
for _ in range(300):
    node_list.append(LRU(c_sz))

for _ in range(q):
    ff, name = input().split()
    ff, ss = compressed_node_data.get_node_info(int(ff))

    # get nearest cache node
    if ff not in dp:
        min_v = 0x3f3f3f3f
        temp = -1
        for lo in range(0, m):
            if compressed_node_data.get_node_type_with_compressed(lo) != 'C':
                continue
            if dist[ff][lo] < min_v:
                min_v = dist[ff][lo]
                temp = lo
        dp[ff] = temp
    cc = dp[ff]
    # get bucket node
    bb = compressed_node_data.get_bucket_node()
    # ff ~ cc, cc ~ bb
    ans = 2 * dist[ff][cc]
    if not node_list[cc].access_station_data(name):
        ans = ans + 2 * dist[cc][bb]
    print(f'{ans}\n')
