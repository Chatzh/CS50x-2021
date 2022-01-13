import csv
import sys


def main():
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    database = 0

    STRs = []
    with open(sys.argv[1], "r") as csv_file:
        reader = csv.DictReader(csv_file)
        if "large" in sys.argv[1]:
            database = 1
            for STR in reader:
                STR["AGATC"] = int(STR["AGATC"])
                STR["TTTTTTCT"] = int(STR["TTTTTTCT"])
                STR["AATG"] = int(STR["AATG"])
                STR["TCTAG"] = int(STR["TCTAG"])
                STR["GATA"] = int(STR["GATA"])
                STR["TATC"] = int(STR["TATC"])
                STR["GAAA"] = int(STR["GAAA"])
                STR["TCTG"] = int(STR["TCTG"])
                STRs.append(STR)
        else:
            for STR in reader:
                STR["AGATC"] = int(STR["AGATC"])
                STR["AATG"] = int(STR["AATG"])
                STR["TATC"] = int(STR["TATC"])
                STRs.append(STR)

    with open(sys.argv[2], "r") as dna_file:
        dna = dna_file.read()

    counts_large = {
        "AGATC": 0,
        "TTTTTTCT": 0,
        "AATG": 0,
        "TCTAG": 0,
        "GATA": 0,
        "TATC": 0,
        "GAAA": 0,
        "TCTG": 0
    }

    counts_small = {
        "AGATC": 0,
        "AATG": 0,
        "TATC": 0
    }

    strs_large = ["AGATC", "TTTTTTCT", "AATG", "TCTAG", "GATA", "TATC", "GAAA", "TCTG"]
    strs_small = ["AGATC", "AATG", "TATC"]

    if database == 1:
        for i in range(len(strs_large)):
            counts_large[strs_large[i]] = count_STR(strs_large[i], dna)

        for STR in STRs:
            match_count = 0
            for str_ in strs_large:
                if counts_large[str_] == STR[str_]:
                    match_count += 1
            if match_count == 8:
                print(STR["name"])
                sys.exit()
    else:
        for i in range(len(strs_small)):
            counts_small[strs_small[i]] = count_STR(strs_small[i], dna)

        for STR in STRs:
            match_count = 0
            for str_ in strs_small:
                if counts_small[str_] == STR[str_]:
                    match_count += 1
            if match_count == 3:
                print(STR["name"])
                sys.exit()

    print("No match")


def count_STR(str_, dna):
    length = len(str_)
    count = 0
    max_count = 0

    for i in range(length):
        tmp_dna = dna[i:]
        for j in range(0, len(tmp_dna) - length, length):
            count = tmp_dna[j - max_count * length: j + length].count(str_)
            max_count = count if count > max_count else max_count

    return max_count


if __name__ == "__main__":
    main()