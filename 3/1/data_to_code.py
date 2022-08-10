ori_data = []
with open("station.txt", "r") as f:
    ori_data = ["    \"" + k.strip() + "\"" for k in f.readlines()]
with open("base_code.txt", "w") as f:
    f.write("data = [\n")
    s = ",\n".join(ori_data)
    f.write(s)
    f.write("\n]");
