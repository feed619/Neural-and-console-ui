import random

SIZE = 5


def create_weight_layer(uotputs: int, size: int) -> list[float]:
    return [[random.randint(0, 99)*0.1/100 for _ in range(size)] for __ in range(uotputs)]


def prediction_func(list_weighted_sum, threshold=0.5):
    return [1 if weighted_sum >= threshold else 0 for weighted_sum in list_weighted_sum]


def adjust_weights(list_weighted_sum, list_weight_layer, input_data, 
                   answer, prediction, learning_rate=0.1):
    for index in range(len(list_weight_layer)):
        if index == answer:
            error = 1 - prediction
        else:
            error = 0 - prediction
        for i in range(len(list_weight_layer[index])):
            list_weight_layer[index][i] += learning_rate * \
                error * input_data[i]


def predict(input_neural, list_weight_layer):
    output_data = []
    for weight_layer in list_weight_layer:
        weighted_sum = 0
        for i in range(len(input_neural)):
            weighted_sum += input_neural[i]*weight_layer[i]
        output_data.append(weighted_sum)
    return output_data


def get_result(input_data, list_weight_layer, output_data, answer):
    list_weighted_sum = predict(input_data, list_weight_layer)
    print(list_weighted_sum)
    list_prediction = prediction_func(list_weighted_sum)
    print(list_prediction)
    adjust_weights(list_weighted_sum, list_weight_layer, input_data,
                   answer, list_prediction[answer])



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
        0: "O",
        1: "X"
    }

    list_weight_layer = create_weight_layer(2, SIZE**2)

    for i in range(4):
        print(f"Эпоха {i} ---")
        result_1 = get_result(input_data, list_weight_layer, output_data, 1)
        result_2 = get_result(input_data_2, list_weight_layer, output_data, 0)
    # print(f"Результат Эпохи {i} ---", "X--->", result_1, "0--->", result_2)


main()
