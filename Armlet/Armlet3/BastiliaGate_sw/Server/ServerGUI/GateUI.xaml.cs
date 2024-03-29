﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using HonorInterfaces;

namespace ServerGUI
{
    /// <summary>
    /// Interaction logic for GateUI.xaml
    /// </summary>
    public partial class GateUI
    {
        public IGateModel Model { private get; set; }


        public GateUI()
        {
            InitializeComponent();
        }

        private void ActivatePin_OnClick(object sender, RoutedEventArgs e)
        {
            Model.ActivatePin();
        }

        private void WritePillButton_Click(object sender, RoutedEventArgs e)
        {
            int charges;
            if (!int.TryParse(ChargesTextBox.Text, out charges))
            {
                MessageBox.Show("Заряды должны быть числом!");
                return;
            }
            if (charges < 0 || charges > 1000)
            {
                MessageBox.Show("Заряды должны быть от 0 до 1000");
                return;
            }
            var selectedPill = PillTypeBox.SelectedItem;
            if (selectedPill == null)
            {
                MessageBox.Show("Нужно выбрать тип пилюли");
                return;
            }
            Model.WritePill(((IPillType) selectedPill).Id, charges);
        }

        private void GateUI_OnLoaded(object sender, RoutedEventArgs e)
        {
            Model.DeviceOnlineChanged += () => Dispatcher.BeginInvoke(new Action(UpdatePillOnline));
            Model.DeviceDataArrived += obj => Dispatcher.BeginInvoke(new Action(() => UpdatePillDataArrived(obj)));
            Model.GateOnlineChanged += () => Dispatcher.BeginInvoke(new Action(UpdateGateOnline));

            UpdatePillOnline();
            UpdateGateOnline();
            PillTypeBox.ItemsSource = Model.PillTypes; //TODO Use declarative binding
        }

        private void UpdateGateOnline()
        {
            IsEnabled = Model.Online;
            PillGroupBox.Header = "Gate" + (Model.Online ? "Online" : "Offline");
            UpdatePillOnline();
        }

        private void UpdatePillOnline()
        {
            PillGroupBox.Visibility = Model.DeviceOnline ? Visibility.Visible : Visibility.Collapsed;
        }

        private void UpdatePillDataArrived(IEnumerable<byte> obj)
        {
            PillContentBox.Text = string.Join(" ", obj.Select(b => b.ToString("X2")));
        }

        private void UpdateButton_Click(object sender, RoutedEventArgs e)
        {
            Model.RefreshPillStatus();
        }
    }
}
