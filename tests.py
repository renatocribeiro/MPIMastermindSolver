import subprocess
import time
import numpy as np
import pickle
import os
import glob
import matplotlib.pyplot as plt

"""
BASIC 'BENCHMARK' SCRIPT
"""

cmd = "mpiexec -n {} cmake-build-debug/mastermind_solver c {} s {} r {} h {}"

def bench_runtime():
    n = 4
    c = 5
    s = 5
    h = 100

    it = 200
    d = {}
    fname = "runtime_{}_{}_{}_{}_{}.pkl".format(n, c, s, h, it)

    if(not os.path.isfile("./{}".format(fname))):
        for regen in [0, 1]:
            l = []
            for _ in range(it):
                print(_)
                beg = time.time()
                subprocess.check_output(cmd.format(n, c, s, regen, h).split())
                end = time.time() - beg
                l.append(end)
            d[str(regen)] = l
            with open(fname, "wb") as output_file:
                pickle.dump(d, output_file)
    

    with open(fname, "rb") as input_file:
        d = pickle.load(input_file)
    #fig, ax = plt.subplots(nrows=1, ncols=len(d.keys()), sharey = True, sharex = True)
    fig, ax = plt.subplots()

    for i, key in enumerate(d.keys()):
        print(i, key)
        ax.hist(d[key], density = False, alpha = 0.7, label = "With Regen" if key == "1" else "Without Regen", histtype="step", linewidth = 2)
    ax.legend()
    plt.show()

def bench_all():
    perc = [0.1, 0.5, 0.9]
    cc = [6, 8, 9]
    ss = [4, 5, 6]
    regen = [1, 0]
    it = 100
    n = 4
    nbr_rounds = 0

    for p in perc:
        fname = "all_{}.pkl".format(p)
        print(fname)
        d = {}
        for c in cc:
            for s in ss:
                tot = np.power(c, s)
                secret = int(p*tot)
                r_d = {}
                for r in regen:
                    r_rounds, r_time = [], []
                    for i in range(it):
                        beg = time.time()
                        o = str(subprocess.check_output(cmd.format(n, c, s, r, secret).split()))
                        try:
                            oo = subprocess.check_output("killall mastermind_hydra".split())
                        except Exception as e:
                            pass
                        end = time.time() - beg
                        nbr_rounds = o[o.rfind("in")+2:o.rfind("rounds")].strip()
                        r_rounds.append(nbr_rounds)
                        r_time.append(end)
                    r_d[r] = {"time" : r_time, "rounds" : r_rounds}
                d[(c, s)] = r_d
                print("({},{})".format(c, s))
        with open(fname, "wb") as output_file:
            pickle.dump(d, output_file)

def plot_all():
    with_color = "red"
    without_color = "blue"
    #perc = [0.1, 0.5, 0.9]
    perc = [0.1, 0.5, 0.9]
    
    for p in perc:
        fname = "all_{}.pkl".format(p)
        with open(fname, "rb") as output_file:
            d = pickle.load(output_file)
        #print(d)
        cc = [6, 8, 9]
        ss = [4, 5, 6]
        fig, ax = plt.subplots(nrows=len(ss), ncols=len(cc), sharey = True, figsize=(12,9))
        for i, c in enumerate(cc):
            for j, s in enumerate(ss):
                current = (c, s)
                current_ax = ax[i][j]
                #time_with_regen = [int(elem) for elem in d[current][1]["rounds"] if elem.isdigit()]
                #time_without_regen = [int(elem) for elem in d[current][0]["rounds"] if elem.isdigit()]
                time_with_regen = d[current][1]["time"]
                time_without_regen = d[current][0]["time"]
                if (i == 0 and j == 0):
                    w, _, _ = current_ax.hist(time_with_regen, label="Regen", alpha = 0.4, color = with_color)
                    wo, _, _ = current_ax.hist(time_without_regen, label="No Regen", alpha = 0.4, color = without_color)
                else:
                    w, _, _ = current_ax.hist(time_with_regen, alpha = 0.4, color = with_color)
                    wo, _, _ = current_ax.hist(time_without_regen, alpha = 0.4, color = without_color)           
                current_ax.plot((np.average(time_with_regen), np.average(time_with_regen)), (0, np.max(w)), color = with_color, label = r'$\bar{x}_{r}=$' + "{:.2f}".format(np.average(time_with_regen)))
                current_ax.plot((np.average(time_without_regen), np.average(time_without_regen)), (0, np.max(wo)), color = without_color, label = r'$\bar{x}_{nr}=$' + "{:.2f}".format(np.average(time_without_regen)))
                current_ax.legend()
                #current_time = d[current][]
                #current_ax.plot([2,3],[1,2])

        for col, s in zip(ax[0], ss):
            anot = "s = {}".format(s)
            col.annotate(anot, xy=(0.5, 1), xytext=(0, 5),
            xycoords='axes fraction', textcoords='offset points',
            size='large', ha='center', va='baseline')

        for row, c in zip(ax, cc):
            anot = "c = {}".format(c)
            row[0].annotate(anot, xy=(0.5, 1), xytext=(-row[0].yaxis.labelpad, 0),
            xycoords=row[0].yaxis.label, textcoords='offset points',
            size='large', ha='right', va='center', rotation = 90)
        fig.suptitle("Distribution of runtime (in seconds) for a secret at position $p={}$".format(p), fontsize=18)
        #plt.show()
        #fig.set_size_inches(12, 9)
        fig.set_dpi(300)
        #plt.tight_layout()
        plt.subplots_adjust(wspace=0.05, hspace=0.1)
        plt.savefig(fname+".png")


def main():
    #bench_runtime()
    #bench_all()
    #o = str(subprocess.check_output("mpiexec -n 4 mastermind_hydra c 3 s 3".format().split()))
    #print(o)
    plot_all()

main()
