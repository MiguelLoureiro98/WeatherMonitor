import numpy as np
from scipy.optimize import lsq_linear
import matplotlib.pyplot as plt

def print_params(params: list) -> None:

    print("Fitted curve");
    print("-" * 12);
    print(f"log(Lux) = {params[1]} * log(R) + {params[0]}");

    return;

def plot_fit(Rdata: np.ndarray, Ldata: np.ndarray, params: list) -> None:

    fig = plt.figure(figsize=(5, 5));
    ax = fig.subplots(1, 1);

    ax.set_title("Fitted curve");
    ax.set_xlabel("log R (kOhm)");
    ax.set_ylabel("log Light (Lux)");
    ax.scatter(Rdata, Ldata, color="b", label="Data");
    ax.plot(Rdata, params[1] * Rdata + params[0], color="r", label="Fit");
    ax.legend();
    ax.grid();

    plt.show();

    return;

if __name__ == "__main__":

    Rdatamin = np.log10(np.array([55, 40, 30, 20, 12, 8, 5, 4]));
    Ldatamin = np.log10(np.array([1, 2, 3, 6, 20, 30, 60, 100]));
    Amin = np.hstack((np.ones((Rdatamin.shape[0], 1)), np.expand_dims(Rdatamin, axis=1)));

    resultmin = lsq_linear(Amin, Ldatamin);

    print_params(resultmin.x);
    plot_fit(Rdatamin, Ldatamin, resultmin.x);

    Rdatamax = np.log10(np.array([280, 90, 70, 60, 50, 20, 10, 7.5]));
    Ldatamax = np.log10(np.array([1, 4, 5, 6, 10, 30, 70, 100]));
    Amax = np.hstack((np.ones((Rdatamax.shape[0], 1)), np.expand_dims(Rdatamax, axis=1)));

    resultmax = lsq_linear(Amax, Ldatamax);

    print_params(resultmax.x);
    plot_fit(Rdatamax, Ldatamax, resultmax.x);