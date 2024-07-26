using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WPFRegisterStudent
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Course choice;
        int hours = 0;


        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {

            Course course1 = new Course("IT 145");
            Course course2 = new Course("IT 200");
            Course course3 = new Course("IT 201");
            Course course4 = new Course("IT 270");
            Course course5 = new Course("IT 315");
            Course course6 = new Course("IT 328");
            Course course7 = new Course("IT 330");


            this.comboBox.Items.Add(course1);
            this.comboBox.Items.Add(course2);
            this.comboBox.Items.Add(course3);
            this.comboBox.Items.Add(course4);
            this.comboBox.Items.Add(course5);
            this.comboBox.Items.Add(course6);
            this.comboBox.Items.Add(course7);


            this.textBox.Text = hours.ToString();
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            choice = (Course)(this.comboBox.SelectedItem);
            
            if (!choice.IsRegisteredAlready()) // check if the class has already been registered.
            {
                if (hours < 9) // check if the credit hour max has been reached.
                    {
                        this.listBox.Items.Add(choice); // add item to listbox
                        this.choice.SetToRegistered(); // changes bool value in the selected class to true.
                        hours = hours + 3; // add 3 hours per course
                        this.textBox.Text = hours.ToString(); // convert hours to string and show in textbox
                        label3.Content = "Registration confirmed for " + choice; // display feedback to the user in a label
                    }
                else // error message for exceeding credit hours
                {
                    label3.Content = "You cannot register for more than 9 credit hours."; 
                }
            }
            else // error message for duplicate registration
            {
                label3.Content = "You have already registered for this " + choice + " course.";
            }

        }

    }
}
