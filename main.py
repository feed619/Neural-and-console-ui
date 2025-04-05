import random

SIZE = 28


def create_weight_layer(size: int)-> list[float]:
    return [random.randint(0, 99)*0.1/100 for _ in range(size)]


def prediction_func(value, threshold=0.5):
    return 1 if value >= threshold else 0


def adjust_weights(weight_layer, input_data, answer, prediction, learning_rate=0.1):
    error = answer - prediction
    for i in range(len(weight_layer)):
        weight_layer[i] += learning_rate * error * input_data[i]


def predict(input_neural, weight_layer):
    weighted_sum = 0
    for i in range(len(input_neural)):
        weighted_sum += input_neural[i]*weight_layer[i]
    return weighted_sum


def get_result(input_data, weight_layer, output_data, answer):
    weighted_sum = predict(input_data, weight_layer)
    print(weighted_sum)
    prediction = prediction_func(weighted_sum)
    print(prediction)
    adjust_weights(weight_layer, input_data, answer, prediction)
    return (output_data[prediction])


def main():
    input_data = [
        1, 0, 0, 0, 1,
        0, 1, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 1, 0, 1, 0,
        1, 0, 0, 0, 1,
    ]
    input_data_2 = [
        0, 0, 1, 0, 0,
        0, 1, 0, 1, 0,
        0, 1, 0, 1, 0,
        0, 1, 0, 1, 0,
        0, 0, 1, 0, 0,
    ]
    output_data = {
        1: "X",
        0: "O"
    }

    weight_layer = create_weight_layer(SIZE**2)

    for i in range(10):
        # print("Эпоха 1 ---", weight_layer)
        result_1 = get_result(input_data, weight_layer, output_data, 1)
        result_2 = get_result(input_data_2, weight_layer, output_data, 0)
        print(f"Результат Эпохи {i} ---", "X--->", result_1, "0--->", result_2)


main()
