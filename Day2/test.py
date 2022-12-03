print(
    sum(
        [
            {"X": 0, "Y": 3, "Z": 6}[x[1]]
            + {"A": 1, "B": 2, "C": 3}[
                (lambda o, m:
                 o if m == 'Y'
                 else
                 'B' if ((m == 'Z' and o == 'A') or (m == 'X' and o == 'C'))
                 else
                 'C' if ((m == 'Z' and o == 'B') or (m == 'X' and o == 'A'))
                 else
                 'A')(x[0], x[1])
            ]
            for x in [i for i in [
                (y.split()) for y in open("input.txt").readlines()
            ]]]))
