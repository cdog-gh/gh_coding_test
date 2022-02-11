import sys
from decimal import Decimal

my_input = sys.stdin.readline


def init_gyeongbu_line_station_info():
    arr = [
        '1	Seoul	0.0	Y	23	Chupungnyeong	234.7	N',
        '2	Yeongdeungpo	9.1	Y	24	Gimcheon	253.8	Y',
        '3	Anyang	23.9	N	25	Gumi	276.7	Y',
        '4	Suwon	41.5	Y	26	Sagok	281.3	N',
        '5	Osan	56.5	N	27	Yangmok	289.5	N',
        '6	Seojeongri	66.5	N	28	Waegwan	296.0	Y',
        '7	Pyeongtaek	75.0	Y	29	Sindong	305.9	N',
        '8	Seonghwan	84.4	N	30	Daegu	323.1	Y',
        '9	Cheonan	96.6	Y	31	Dongdaegu	326.3	Y',
        '10	Sojeongni	107.4	N	32	Gyeongsan	338.6	N',
        '11	Jeonui	114.9	N	33	Namseonghyeon	353.1	N',
        '12	Jochiwon	129.3	Y	34	Cheongdo	361.8	N',
        '13	Bugang	139.8	N	35	Sangdong	372.2	N',
        '14	Sintanjin	151.9	N	36	Miryang	381.6	Y',
        '15	Daejeon	166.3	Y	37	Samnangjin	394.1	N',
        '16	Okcheon	182.5	N	38	Wondong	403.2	N',
        '17	Iwon	190.8	N	39	Mulgeum	412.4	N',
        '18	Jitan	196.4	N	40	Hwamyeong	421.8	N',
        '19	Simcheon	200.8	N	41	Gupo	425.2	Y',
        '20	Gakgye	204.6	N	42	Sasang	430.3	N',
        '21	Yeongdong	211.6	Y	43	Busan	441.7	Y',
        '22	Hwanggan	226.2	N',
    ]
    dic = {}
    for target in arr:
        items = target.split()
        dic[items[1]] = Decimal(items[2])
        if len(items) > 7:
            dic[items[5]] = Decimal(items[6])
    return dic


def time_to_num(time):
    return 60 * int(time[0:2]) + int(time[3:5])


# 경부선 역 정보 얻어오기.
gb_info = init_gyeongbu_line_station_info()
n, q = map(int, my_input().split(' '))
s_dic = {}
s_list = []
for i in range(n):
    # station_name hh:mm hh:mm
    dia = my_input().split(' ')
    s_list.append(dia[0])
    s_dic[dia[0]] = tuple(dia)

for i in range(q):
    s = my_input().split(' ')
    s[1] = s[1].replace('\n', '')

    # 거리 구하기
    dist = abs(gb_info[s[1]] - gb_info[s[0]])
    # 시간 구하기
    t0 = time_to_num(s_dic[s[0]][2])  # 출발 시각
    t1 = time_to_num(s_dic[s[1]][1])  # 도착 시각
    if t0 > t1:
        t1 = t1 + 24 * 60
    delta_min = t1 - t0
    # delta_min 분 동안 dist 만큼 갔으므로 60분 동안 dist * 60 / delta_min 만큼 감.
    # 그런데 23.9km를 단위 거리 239로 바꾸었으므로, 추가로 10으로 나누어야 함.
    # 따라서 답은 (dist * 6) // delta_min
    ans = (dist * 60) // delta_min
    print(f'{ans}')
