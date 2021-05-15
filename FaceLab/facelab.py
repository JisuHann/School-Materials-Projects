import numpy as np
from keras.callbacks import EarlyStopping
from sklearn.model_selection import train_test_split
from keras.models import Sequential
from keras.layers import Dense , Activation , Dropout ,Flatten
from keras.layers.convolutional import Conv2D
from keras.layers.convolutional import MaxPooling2D
from keras.metrics import categorical_accuracy
from keras.models import model_from_json
from keras.optimizers import *
from keras.layers.normalization import BatchNormalization


def getData(filname):
    # images are 48x48
    # N = 35887
    Y = []
    X = []
    first = True
    for line in open(filname):
        if first:
            first = False
        else:
            row = line.split(',')
            Y.append(int(row[0]))
            X.append([int(p) for p in row[1].split()])

    X, Y = np.array(X) / 255.0, np.array(Y)
    return X, Y


#Main CNN model with four Convolution layer & two fully connected layer
def baseline_model():
    # Initialising the CNN
    model = Sequential()

    # 1 - Convolution
    model.add(Conv2D(64,(3,3), padding='same', input_shape=(48, 48,1)))
    model.add(BatchNormalization())
    model.add(Activation('relu'))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    model.add(Dropout(0.25))

    # 2nd Convolution layer
    model.add(Conv2D(128,(5,5), padding='same'))
    model.add(BatchNormalization())
    model.add(Activation('relu'))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    model.add(Dropout(0.25))

    # 3rd Convolution layer
    model.add(Conv2D(512,(3,3), padding='same'))
    model.add(BatchNormalization())
    model.add(Activation('relu'))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    model.add(Dropout(0.25))

    # 4th Convolution layer
    model.add(Conv2D(512,(3,3), padding='same'))
    model.add(BatchNormalization())
    model.add(Activation('relu'))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    model.add(Dropout(0.25))


    # Flattening
    model.add(Flatten())

    # Fully connected layer 1st layer
    model.add(Dense(256))
    model.add(BatchNormalization())
    model.add(Activation('relu'))
    model.add(Dropout(0.25))


    # Fully connected layer 2nd layer
    model.add(Dense(512))
    model.add(BatchNormalization())
    model.add(Activation('relu'))
    model.add(Dropout(0.25))

    model.add(Dense(num_class, activation='sigmoid'))

    model.compile(optimizer='adam', loss='binary_crossentropy', metrics=[categorical_accuracy])

    es = EarlyStopping(monitor='val_acc', patience=2)
    return model, es


def baseline_model_saved():
    model = load_model("model_4layer_2_2_pool.h5")
    model.compile(optimizer='adam', loss='binary_crossentropy', metrics=[categorical_accuracy])
    return model


if __name__ == '__main__':

    # get the data
    filname = 'challenges-in-representation-learning-facial-expression-recognition-challenge\\fer2013\\fer2013.csv'
    label_map = ['Anger', 'Disgust', 'Fear', 'Happy', 'Sad', 'Surprise', 'Neutral']
    
    X, Y = getData(filname)
    num_class = len(set(Y))

    # keras with tensorflow backend
    N, D = X.shape
    X = X.reshape(N, 48, 48, 1)

    # Split in  training set : validation set :  testing set in 80:10:10
    X_train, X_test, y_train, y_test = train_test_split(X, Y, test_size=0.1, random_state=0)
    y_train = (np.arange(num_class) == y_train[:, None]).astype(np.float32)
    y_test = (np.arange(num_class) == y_test[:, None]).astype(np.float32)

    batch_size = 128
    epochs = 124

    is_model_saved = False

    # If model is not saved train the CNN model otherwise just load the weights
    if(is_model_saved==False ):
        # Train model
        model, es = baseline_model()
        # Note : 3259 samples is used as validation data &   28,709  as training samples

        model.fit(X_train, y_train,
                  batch_size=batch_size,
                  epochs=epochs,
                  verbose=2,
                  validation_split=0.1111,
                  callbacks=[es])
        
        model.save("model_4layer_2_2_pool.h5")
        print("Saved model to disk")
    else:
        # Load the trained model
        print("Load model from disk")
        model = baseline_model_saved()


    # Model will predict the probability values for 7 labels for a test image
    score = model.predict(X_test)
    print (model.summary())

    new_X = [ np.argmax(item) for item in score ]
    y_test2 = [ np.argmax(item) for item in y_test]

    # Calculating categorical accuracy taking label having highest probability
    accuracy = [ (x==y) for x,y in zip(new_X,y_test2) ]
    print(" Accuracy on Test set : " , np.mean(accuracy))
