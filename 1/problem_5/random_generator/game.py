class game:
    def __init__(self, rc_num):
        self.rc_num = rc_num
        self.resource = dict()  # 사용하는 리소스
        self.card = dict()  # card 에 대한 정보
        self.player = [0] * 500001

    def get_resource_owner(self, rn):
        if rn not in self.resource:
            return -1
        return self.resource.get(rn)

    # card_op = card_id, oper, num tuple
    def is_available(self, pn, card_op):
        _, oper, num = card_op
        # next 인 경우에는 무조건 True 이다.
        if oper == 'next':
            return True
        if oper == 'release':
            return self.get_resource_owner(num) == pn
        if oper == 'acquire':
            return self.get_resource_owner(num) != pn

    def current_card(self, pn):
        if self.player[pn] == 0:
            return None
        return self.card[self.player[pn]]

    def process_turn(self, pn, card_op):
        cid, oper, num = card_op
        self.card[cid] = card_op
        if oper == 'next':
            self.player[pn] = 0
            return
        elif oper == 'acquire':
            if self.get_resource_owner(num) != pn and self.get_resource_owner(num) != -1:
                self.player[pn] = cid
            else:
                self.player[pn] = 0
                self.resource[num] = pn
        else:
            if self.get_resource_owner(num) == pn:
                self.player[pn] = 0
                self.resource.pop(num)
            else:
                exit(-1)
