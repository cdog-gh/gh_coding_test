s = input()
if s[-1] == ')':
    main, sub = s.replace(")", "").split("(")
    print(main.strip() + " ")
    print(sub.strip() + " ")
else:
    print(s + " ")
    print("- ")
