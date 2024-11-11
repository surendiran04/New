import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier , plot_tree
from sklearn import metrics
import matplotlib.pyplot as plt
 

# Sample Weather Dataset
data = pd.read_csv('Book1.csv')
# Convert to DataFrame
df = pd.DataFrame(data)

# Convert categorical variables to numeric using one-hot encoding
df_encoded = pd.get_dummies(df[['Outlook', 'Temperature', 'Humidity', 'Windy']])
y = df['Play'].apply(lambda x: 1 if x == 'Yes' else 0)  # Target variable: 1 for 'Yes', 0 for 'No'

# Split data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(df_encoded, y, test_size=0.3, random_state=42)

# Initialize the Decision Tree Classifier
clf = DecisionTreeClassifier(criterion = 'entropy', random_state=42)

# Train the classifier
clf.fit(X_train, y_train)

# Make predictions on the test set
y_pred = clf.predict(X_test)

# Evaluate the model
accuracy = metrics.accuracy_score(y_test, y_pred)
print(f"Accuracy: {accuracy:.2f}")

# Visualize the Decision Tree
plt.figure(figsize=(12, 8))
plot_tree(clf, filled=True, feature_names=df_encoded.columns, class_names=['No', 'Yes'], rounded=True)
plt.show()
tree_rules = export_text(dt_classifier, feature_names=['Outlook', 'Temperature', 'Humidity', 'Windy'])
print("\nDecision Tree Rules:")
print(tree_rules)
